from experta import Fact, KnowledgeEngine, Rule, NOT, MATCH

class ArrayProperty(Fact):
    """Свойство массива или требование к алгоритму."""
    pass

class Algorithm(Fact):
    """Рекомендованный алгоритм."""
    pass

class SortEngine(KnowledgeEngine):

    
    @Rule(NOT(ArrayProperty(name='volume')))
    def ask_volume(self):
        value = input("Объем данных (малый/средний/большой/неизвестно): ").strip().lower()
        self.declare(ArrayProperty(name='volume', value=value))

    @Rule(NOT(ArrayProperty(name='memory')))
    def ask_memory(self):
        value = input("Ограничения по памяти (строгие/гибкие/неизвестно): ").strip().lower()
        self.declare(ArrayProperty(name='memory', value=value))

    @Rule(NOT(ArrayProperty(name='stability')))
    def ask_stability(self):
        value = input("Нужна ли стабильность сортировки? (да/нет/неизвестно): ").strip().lower()
        self.declare(ArrayProperty(name='stability', value=value))

    @Rule(NOT(ArrayProperty(name='partially_sorted')))
    def ask_sorted(self):
        value = input("Данные уже почти отсортированы? (да/нет/неизвестно): ").strip().lower()
        self.declare(ArrayProperty(name='partially_sorted', value=value))

    @Rule(
        ArrayProperty(name='volume', value='малый')
    )
    def rule_small_volume(self):
        self.declare(Algorithm(name='Сортировка вставками'))
        print("\n  Вывод: Рекомендуется Сортировка вставками.")


    @Rule(
        ArrayProperty(name='volume', value='большой'),
        ArrayProperty(name='memory', value='гибкие'),
        ArrayProperty(name='stability', value='нет')
    )
    def rule_large_flex_unstable(self):
        self.declare(Algorithm(name='Быстрая сортировка'))
        print("\n  Вывод: Рекомендуется Быстрая сортировка.")

    @Rule(
        ArrayProperty(name='volume', value='большой'),
        ArrayProperty(name='memory', value='гибкие'),
        ArrayProperty(name='stability', value='да')
    )
    def rule_large_flex_stable(self):
        self.declare(Algorithm(name='Сортировка слиянием'))
        print("\n  Вывод: Рекомендуется Сортировка слиянием.")

    @Rule(
        ArrayProperty(name='volume', value='большой'),
        ArrayProperty(name='memory', value='строгие'),
        ArrayProperty(name='stability', value='нет')
    )
    def rule_large_strict_unstable(self):
        self.declare(Algorithm(name='Пирамидальная сортировка'))
        print("\n  Вывод: Рекомендуется Пирамидальная сортировка.")

    @Rule(
        ArrayProperty(name='volume', value='большой'),
        ArrayProperty(name='memory', value='строгие'),
        ArrayProperty(name='stability', value='да')
    )
    def rule_large_strict_stable(self):
        self.declare(Algorithm(name='Block Sort или TimSort'))
        print("\n  Вывод: Рекомендуется Блочная сортировка.")

    @Rule(
        ArrayProperty(name='volume', value='средний'),
        ArrayProperty(name='memory', value='строгие')
    )
    def rule_medium_strict(self):
        self.declare(Algorithm(name='Пирамидальная сортировка'))
        print("\n  Вывод: Рекомендуется Пирамидальная сортировка.")

    @Rule(
        ArrayProperty(name='volume', value='средний'),
        ArrayProperty(name='memory', value='гибкие')
    )
    def rule_medium_flexible(self):
        self.declare(Algorithm(name='Быстрая сортировка'))
        print("\n  Вывод: Рекомендуется Быстрая сортировка.")

    @Rule(
        ArrayProperty(name='volume', value=MATCH.v),
        ArrayProperty(name='memory', value=MATCH.m),
        ArrayProperty(name='stability', value=MATCH.s),
        ArrayProperty(name='partially_sorted', value=MATCH.p),
        NOT(Algorithm()),
        salience=-10
    )
    def unknown(self):
        print("\n  Не удалось подобрать идеальный алгоритм под ваши специфические условия.")

if __name__ == "__main__":
    engine = SortEngine()
    engine.reset()
    engine.run()