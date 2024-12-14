#include <iostream>
#include <vector>

using namespace std;


void bub(int list[], int num)
{
    int num1, num2;

	while(num--)
	{
		bool swapped = false;
		
		for(int i = 0; i < num; i++)
		{
			if(list[i] > list[i + 1])
			{
				num1 = list[i];
                num2 = list[i+1];
                list[i+1] = num1;
                list[i] = num2;
                swapped = true;
			}
		}
		
		if(swapped == false)
			break;
	}
}

void printv(vector<int> obj, string message){
    cout << message;
    for(int i=0; i < obj.size(); i++)
    {
        if(i!=obj.size()-1)
            cout << obj.at(i) << ", ";
        else
            cout << obj.at(i);
    }
    cout << "} " << obj.size() << " \n \n";
}

void print(int obj[], int num, string message){
    cout << message;
    for(int i=0; i < num; i++)
    {
        if(i!=num-1)
            cout << obj[i] << ", ";
        else
            cout << obj[i];
    }

    cout << "} " << num << " \n \n";
}

int main()
{
    int i, n, k, l, t, pluscount, Ufirst, Ulast;

    cout << "все вводимые значения должны относятся к множеству целых чисел \n";

    // U
    cout << "Введите начальное значение универсума: ";
    cin >> Ufirst;

    cout << "Введите конечное значение универсума: ";
    cin >> Ulast;

    vector <int> Universum;
    for(i = Ufirst; i <= Ulast; i++){
        Universum.push_back(i);
    }

    // A
    cout << "Введите мощность множества А: ";
    cin >> n;
    int A[n];
    if(n != 0)
        cout << "Введите члены множества А (через enter): ";
    for(i = 0; i < n; i++)
    {
        cin >> l;
        if (i == 0){
            if(l >= Ufirst && l <= Ulast){
                A[i] = l;
            }
            else
            {
                cout << "Введен элемент, нарушающий условие! \n";
                i = -1;
            }
        }
        else {
            for(t = 0; t < i; ++t) {
                if(l != A[t] && l>=Ufirst && l<=Ulast){
                    A[i] = l;
                }
                else {
                    cout << "Введен элемент, нарушающий условие! \n";
                    i--;
                    break;
                }
            }
        }
    }

    // B
    cout << "Введите мощность множества B: ";
    cin >> k;
    int B[k];
    if(k != 0)
        cout << "Введите члены множества B (через enter): ";
    for(i = 0; i < k; i++)
    {
        cin >> l;
        if (i == 0){
            if(l>=Ufirst && l<=Ulast){
                B[i] = l;
            }
            else
            {
                cout << "Введен элемент, нарушающий условие! \n";
                i = -1;
            }
        }
        else {
            for(t = 0; t < i; ++t) {
                if(l != B[t] && l>=Ufirst && l<=Ulast){
                    B[i] = l;
                }
                else {
                    cout << "Введен элемент, нарушающий условие! \n";
                    i--;
                    break;
                }
            }
        }
    }
    bub(A, n);
    bub(B, k);

    // объединение
    vector <int> Plus;
    for(i = 0; i<n; i++)
    {
        Plus.push_back(A[i]);
    }
    for(i = 0; i<k; i++)
    {
        pluscount = 0;
        for(t=0; t< Plus.size(); t++){
            if(B[i]==Plus.at(t)){
                ++pluscount;
            }
        }
        if(pluscount==0){
            Plus.push_back(B[i]); 
            t = Plus.size();
            pluscount = 0;
        }
    }

    // sort vector
    int num1, num2;
    int num = Plus.size();

	while(num--)
	{
		bool swapped = false;
		
		for(int i = 0; i < num; i++)
		{
			if(Plus.at(i) > Plus.at(i + 1))
			{
				num1 = Plus.at(i);
                num2 = Plus.at(i+1);
                Plus.at(i+1) = num1;
                Plus.at(i) = num2;
                swapped = true;
			}
		}
		
		if(swapped == false)
			break;
	}

    // разность A/B
    vector <int> MinusA;
    for(i = 0; i<n; i++)
    {
        for(t=0; t<k; t++){
            if(A[i]==B[t]){
                break;
            }
            if(t==k-1){
                MinusA.push_back(A[i]);
            }
        }
    }
    
    // разность B/A
    vector <int> MinusB;
    for(i = 0; i<k; i++)
    {
        for(t=0; t<n; t++){
            if(B[i]==A[t]){
                break;
            }
            if(t==n-1){
                MinusB.push_back(B[i]);
            }
        }
    }

    // Симметричная разность
    vector <int> Simt;
    for(i=0; i<MinusA.size(); i++){
        Simt.push_back(MinusA.at(i));
    }
    for(i=0; i<MinusB.size(); i++){
        Simt.push_back(MinusB.at(i));
    }

    // дополнение A
    vector <int> DopolA;
    for(i = 0; i<Universum.size(); i++)
    {
        for(t=0; t<n; t++){
            if(Universum.at(i)==A[t]){
                break;
            }
            if(t==n-1){
                DopolA.push_back(Universum.at(i));
            }
        }
    }

    // дополнение B
    vector <int> DopolB;
    for(i = 0; i<Universum.size(); i++)
    {
        for(t=0; t<k; t++){
            if(Universum.at(i)==B[t]){
                break;
            }
            if(t==k-1){
                DopolB.push_back(Universum.at(i));
            }
        }
    }

    // пересечение
    vector <int> Cross;
    for(i = 0; i<Plus.size(); i++)
    {
        for(t = 0; t<Simt.size(); t++){
            if(Plus[i]==Simt[t]){
                break;
            }
            if(t==Simt.size()-1){
                Cross.push_back(Plus[i]);
            }
        }
    }

    // Вывод A
    print(A, n, "\nмножество A: { ");

    // Вывод В
    print(B, k, "множество B: { ");
    
    // Универсум
    printv(Universum, "Универсум: { ");
    
    // Объединение вывод
    printv(Plus, "объединение A⋃B: { ");

    // пересечение
    printv(Cross, "пересечение: { ");

    // Разность A/B вывод
    printv(MinusA, "разность A/B: { ");

    // симметричная разность вывод
    printv(Simt, "симметричная разность: { ");

    // дополнение А
    printv(DopolA, "дополнение А: { ");

    return 0;
}
