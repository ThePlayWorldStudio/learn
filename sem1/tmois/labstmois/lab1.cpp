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


int main()
{
    int i, n, k, l, t, pluscount, Ufirst, Ulast;

    cout << "все вводимые значения должны относятся к множеству натуральных чисел /\n";

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
                cout << "введен неверный элемент \n";
                i = -1;
            }
        }
        else {
            for(t = 0; t < i; ++t) {
                if(l != A[t] && l>=Ufirst && l<=Ulast){
                    A[i] = l;
                }
                else {
                    cout << "Элементы не могут повторяться! \n";
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
                cout << "введен неверный элемент \n";
                i = -1;
            }
        }
        else {
            for(t = 0; t < i; ++t) {
                if(l != B[t] && l>=Ufirst && l<=Ulast){
                    B[i] = l;
                }
                else {
                    cout << "Элементы не могут повторяться! \n";
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
            // cout<<pluscount<<"\n";
        }
        if(pluscount==0){
            Plus.push_back(B[i]); 
            t = Plus.size();
            pluscount = 0;
        }
    }

    // sort
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
    // Пересечение

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

    vector <int> Razb;
    

    // Вывод A
    // bub(A, n);
    cout << "множество A: { ";
    for(i=0; i < n; i++)
    {
        if(i!=n-1)
            cout << A[i] << ", ";
        else
            cout << A[i];
    }

    cout << "} " << n << " \n \n";

    // Вывод В
    // bub(B, k);
    cout << "множество B: { ";
    for(i=0; i < k; i++)
    {
        if(i!=k-1)
            cout << B[i] << ", ";
        else
            cout << B[i];
    }
    cout << "} " << k << " \n \n";
    
    // Универсум
    cout << "Универсум: { ";
    for(i=0; i < Universum.size(); i++)
    {
        if(i!=Universum.size()-1)
            cout << Universum.at(i) << ", ";
        else
            cout << Universum.at(i);
    }
    cout << "} " << Universum.size() << " \n \n";
    
    // Объединение вывод
    cout << "объединение A⋃B: { ";
    for(i=0; i < Plus.size(); i++)
    {
        if(i!=Plus.size()-1)
            cout << Plus.at(i) << ", ";
        else
            cout << Plus.at(i);
    }
    cout << "} " << Plus.size() << " \n \n";

    // Разность A/B вывод
    cout << "разность A/B: { ";
    for(i=0; i < MinusA.size(); i++)
    {
        if(i!=MinusA.size()-1)
            cout << MinusA.at(i) << ", ";
        else
            cout << MinusA.at(i);
    }
    cout << "} " << MinusA.size() << " \n \n";

    // Разность B/A вывод
    cout << "разность B/A: { ";
    for(i=0; i < MinusB.size(); i++)
    {
        if(i!=MinusB.size()-1)
            cout << MinusB.at(i) << ", ";
        else
            cout << MinusB.at(i);
    }
    cout << "} " << MinusB.size() << " \n \n";

    // симметричная разность вывод
    cout << "симметричная разность: { ";
    for(i=0; i < Simt.size(); i++)
    {
        if(i!=Simt.size()-1)
            cout << Simt.at(i) << ", ";
        else
            cout << Simt.at(i);
    }
    cout << "} " << Simt.size() << " \n \n";

    // дополнение А
    cout << "дополнение А: { ";
    for(i=0; i < DopolA.size(); i++)
    {
        if(i!=DopolA.size()-1)
            cout << DopolA.at(i) << ", ";
        else
            cout << DopolA.at(i);
    }
    cout << "} " << DopolA.size() << " \n \n";

    // дополнение B
    cout << "дополнение B: { ";
    for(i=0; i < DopolB.size(); i++)
    {
        if(i!=DopolB.size()-1)
            cout << DopolB.at(i) << ", ";
        else
            cout << DopolB.at(i);
    }
    cout << "} " << DopolB.size() << " \n \n";

    // пересечение
    cout << "пересечение: { ";
    for(i=0; i < Cross.size(); i++)
    {
        if(i!=Cross.size()-1)
            cout << Cross[i] << ", ";
        else
            cout << Cross[i];
    }
    cout << "} " << Cross.size() << "\n\n";
    return 0;
}
