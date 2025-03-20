#include <iostream>

using namespace std;

class Stak{
private:
    struct Node{
        int value;
        Node* bef = NULL;
    };
    Node* head = NULL;
    
public:
    void push(int data){
        Node* nw = new Node();
        nw->value = data;
        nw->bef = head;
        head = nw;
    }
    
    int peek(){
        if(head!=NULL)
            return head->value;
        else{
            cout << "stack is empty\n";
            return -1;
        }
    }
    
    int pop(){
        if(head){
            Node* temp = head;
            head = head->bef;
            delete temp;
            return 0;
        }
        else{
            cout << "stack is empty\n";
            return -1;
        }
    }
    
    void maximilian(){
        Node* curr = head->bef;
        Node* maxim = head;
        
        while(curr){
            if(curr->value > maxim->value)
                maxim = curr;
            curr = curr->bef;
        }
        
        curr = head;
        while(curr){
            if(curr->bef == maxim){
                curr->bef = maxim->bef;
                delete maxim;
                return;
            }
            curr = curr->bef;
        }
    }
    
    void printall(){
        Node* curr = head;
        while(curr){
            cout << curr->value << " ";
            curr = curr->bef;
        }
        cout << endl;
    }
    
    ~Stak(){
        while (head) {
            pop();
        }
    }
};


int main() {
    Stak bruh;
    
    int iche, num;
    bool iswork = true;
    
    cout << "0. добавить число в стек\n 1. добавить случайное число в стек\n 2. посмотреть числа в стеке\n 3. удалить максимальное значение\n 4. выйти \n\n";
    
    while(iswork){
        cin >> iche;
        switch (iche) {
            case 0:{
                cout << "введите число: ";
                cin >> num;
                bruh.push(num);
                break;
            }
            case 1:{
                bruh.push(rand()%100+1);
                cout << "всё" << endl;
                break;
            }
            case 2:{
                bruh.printall();
                break;
            }
            case 3:{
                bruh.maximilian();
                cout << "всё" << endl;
                break;
            }
            case 4:{
                iswork = false;
            }
            default:
                break;
        }
    }
    return 0;
}
