import tkinter as tk
from tkinter import ttk, messagebox
import numpy as np

class CondorcetApp:
    def __init__(self, root):
        self.root = root
        self.root.title("Кондорсе: Клуб отдыха")
        self.root.geometry("820x720")
        self.root.resizable(True, True)

        # === ЦВЕТА (НЕЗАВИСИМО ОТ ТЕМЫ) ===
        self.bg = "#f8f9fa"
        self.fg = "#000000"        # ЧЁРНЫЙ ТЕКСТ ВЕЗДЕ
        self.btn_bg = "#007bff"
        self.btn_fg = "white"
        self.success = "#28a745"
        self.warning = "#ffc107"
        self.light = "#e9ecef"
        self.border = "#ced4da"

        self.root.configure(bg=self.bg)

        self.alternatives = ["Конный клуб", "Гольф-клуб", "Тренажёрный зал", "Сауна"]
        self.num_alts = 4
        self.rank_spins = []

        self.setup_ui()

    def create_style(self):
        style = ttk.Style()
        style.theme_use('clam')
        style.configure("Custom.TButton",
                        background=self.btn_bg,
                        foreground=self.btn_fg,
                        font=("Segoe UI", 10, "bold"),
                        padding=8)
        style.map("Custom.TButton",
                  background=[('active', '#0056b3')])
        style.configure("Custom.TSpinbox", font=("Segoe UI", 10))

    def setup_ui(self):
        self.create_style()

        # === Заголовок ===
        tk.Label(self.root, text="Принцип Кондорсе\nВыбор клуба отдыха",
                 font=("Segoe UI", 16, "bold"), bg=self.bg, fg=self.fg).pack(pady=15)

        # === Управление ===
        ctrl = tk.Frame(self.root, bg=self.bg)
        ctrl.pack(pady=10, fill=tk.X, padx=20)

        tk.Label(ctrl, text="Экспертов:", bg=self.bg, fg=self.fg, font=("Segoe UI", 11)).pack(side=tk.LEFT)
        self.exp_var = tk.StringVar(value="5")
        spin = ttk.Spinbox(ctrl, from_=1, to=100, textvariable=self.exp_var, width=5, style="Custom.TSpinbox")
        spin.pack(side=tk.LEFT, padx=8)

        ttk.Button(ctrl, text="Начать", style="Custom.TButton", command=self.create_experts).pack(side=tk.LEFT, padx=5)

        # === ПРОКРУЧИВАЕМАЯ ОБЛАСТЬ ДЛЯ ЭКСПЕРТОВ ===
        canvas = tk.Canvas(self.root, bg=self.bg, highlightthickness=0)
        scrollbar = ttk.Scrollbar(self.root, orient="vertical", command=canvas.yview)
        self.experts_container = tk.Frame(canvas, bg=self.bg)

        self.experts_container.bind(
            "<Configure>",
            lambda e: canvas.configure(scrollregion=canvas.bbox("all"))
        )

        canvas.create_window((0, 0), window=self.experts_container, anchor="nw")
        canvas.configure(yscrollcommand=scrollbar.set)

        # === ПРОКРУТКА КОЛЁСИКОМ МЫШИ ВЕЗДЕ ===
        def _on_mousewheel(event):
            canvas.yview_scroll(int(-1*(event.delta/120)), "units")

        def _on_mousewheel_linux(event):
            if event.num == 4:
                canvas.yview_scroll(-1, "units")
            elif event.num == 5:
                canvas.yview_scroll(1, "units")

        canvas.bind_all("<MouseWheel>", _on_mousewheel)  # Windows / macOS
        canvas.bind_all("<Button-4>", _on_mousewheel_linux)  # Linux up
        canvas.bind_all("<Button-5>", _on_mousewheel_linux)  # Linux down

        canvas.pack(side=tk.LEFT, fill=tk.BOTH, expand=True, padx=20, pady=10)
        scrollbar.pack(side=tk.RIGHT, fill=tk.Y)

        # === Результат ===
        self.result = tk.Label(self.root, text="", font=("Segoe UI", 13, "bold"),
                               bg=self.bg, fg=self.success, justify="center")
        self.result.pack(pady=10, fill=tk.X)

        # === Матрица (с горизонтальной прокруткой и чёрным текстом) ===
        matrix_outer = tk.Frame(self.root, bg=self.bg)
        matrix_outer.pack(pady=10, fill=tk.X, padx=20)

        matrix_canvas = tk.Canvas(matrix_outer, bg=self.bg, height=200, highlightthickness=0)
        matrix_scroll_x = ttk.Scrollbar(matrix_outer, orient="horizontal", command=matrix_canvas.xview)
        self.matrix_inner = tk.Frame(matrix_canvas, bg=self.bg)

        self.matrix_inner.bind(
            "<Configure>",
            lambda e: matrix_canvas.configure(scrollregion=matrix_canvas.bbox("all"))
        )

        matrix_canvas.create_window((0, 0), window=self.matrix_inner, anchor="nw")
        matrix_canvas.configure(xscrollcommand=matrix_scroll_x.set)

        matrix_canvas.pack(side=tk.TOP, fill=tk.X, expand=True)
        matrix_scroll_x.pack(side=tk.BOTTOM, fill=tk.X)

    def create_experts(self):
        for widget in self.experts_container.winfo_children():
            widget.destroy()
        for widget in self.matrix_inner.winfo_children():
            widget.destroy()
        self.result.config(text="")
        self.rank_spins = []

        try:
            n = int(self.exp_var.get())
            if n < 1 or n > 100:
                raise ValueError
        except:
            messagebox.showerror("Ошибка", "Введите число от 1 до 100")
            return

        for i in range(n):
            frame = tk.LabelFrame(self.experts_container, text=f" Эксперт {i+1} ",
                                  font=("Segoe UI", 10, "bold"), bg=self.bg, fg=self.fg,
                                  relief="groove", bd=2, padx=12, pady=8)
            frame.pack(fill=tk.X, pady=4, padx=10)

            spins = []
            for j, alt in enumerate(self.alternatives):
                row = tk.Frame(frame, bg=self.bg)
                row.pack(fill=tk.X, pady=3)

                tk.Label(row, text=alt, width=26, anchor="w", bg=self.bg,
                         fg=self.fg, font=("Segoe UI", 10)).pack(side=tk.LEFT, padx=6)

                spin = ttk.Spinbox(row, from_=1, to=4, width=6, style="Custom.TSpinbox", font=("Segoe UI", 10))
                spin.pack(side=tk.RIGHT, padx=6)
                spin.delete(0, "end")
                spin.insert(0, str(j+1))
                spins.append(spin)

            self.rank_spins.append(spins)

        calc_btn = ttk.Button(self.experts_container, text="Рассчитать победителя",
                              style="Custom.TButton", command=self.calculate)
        calc_btn.pack(pady=18)

    def calculate(self):
        n = len(self.rank_spins)
        rankings = []

        try:
            for i, spins in enumerate(self.rank_spins):
                used = set()
                rank = []
                for s in spins:
                    v = int(s.get())
                    if v < 1 or v > 4 or v in used:
                        raise ValueError(f"Эксперт {i+1}: ранг {v} — недопустим или повтор")
                    used.add(v)
                    rank.append(v)
                rankings.append(rank)
        except Exception as e:
            messagebox.showerror("Ошибка ввода", str(e))
            return

        wins = np.zeros((4, 4), dtype=int)
        for rank in rankings:
            order = np.argsort(rank)
            for a in range(4):
                for b in range(a + 1, 4):
                    wins[order[a], order[b]] += 1

        winner = -1
        for i in range(4):
            if all(wins[i, j] > n / 2 for j in range(4) if j != i):
                winner = i
                break

        self.show_matrix(wins)

        if winner != -1:
            self.result.config(text=f"Победитель Кондорсе:\n{self.alternatives[winner]}", fg=self.success)
        else:
            scores = wins.sum(axis=1)
            best = scores.argmax()
            self.result.config(text=f"Нет победителя Кондорсе\nЛучшая: {self.alternatives[best]}\n"
                                    f"({int(scores[best])} из {n} побед)", fg=self.warning)

    def show_matrix(self, wins):
        for widget in self.matrix_inner.winfo_children():
            widget.destroy()

        tk.Label(self.matrix_inner, text="Матрица предпочтений (победы i над j)",
                 font=("Segoe UI", 11, "bold"), bg=self.bg, fg=self.fg).grid(row=0, column=0, columnspan=6, pady=12)

        # Шапка
        tk.Label(self.matrix_inner, text="", width=22, bg=self.light, relief="solid", bd=1,
                 font=("Segoe UI", 9, "bold"), fg=self.fg).grid(row=1, column=0)
        for j, name in enumerate(self.alternatives):
            tk.Label(self.matrix_inner, text=name, width=16, bg=self.light, relief="solid", bd=1,
                     font=("Segoe UI", 9, "bold"), fg=self.fg, wraplength=110).grid(row=1, column=j+1)

        # Строки
        for i in range(4):
            tk.Label(self.matrix_inner, text=self.alternatives[i], width=22, bg=self.light, relief="solid", bd=1,
                     font=("Segoe UI", 9), fg=self.fg, anchor="w", padx=6).grid(row=i+2, column=0, sticky="w")
            for j in range(4):
                if i == j:
                    txt = "—"
                    bg_color = self.light
                else:
                    txt = str(wins[i][j])
                    if wins[i][j] > wins[j][i]:
                        txt = f"**{txt}**"
                        bg_color = "#d4edda"
                    elif wins[i][j] < wins[j][i]:
                        bg_color = "#f8d7da"
                    else:
                        bg_color = self.light
                tk.Label(self.matrix_inner, text=txt, width=16, bg=bg_color, relief="solid", bd=1,
                         font=("Segoe UI", 10, "bold" if "**" in txt else "normal"), fg=self.fg
                         ).grid(row=i+2, column=j+1)


# === ЗАПУСК ===
if __name__ == "__main__":
    root = tk.Tk()
    app = CondorcetApp(root)
    root.mainloop()