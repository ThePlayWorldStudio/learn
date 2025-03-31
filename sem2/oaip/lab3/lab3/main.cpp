#include <iostream>
#include <time.h>

using namespace std;

struct Node{
    int value;
    Node* bef = NULL;
};

class Stak: public Node{
private:
    
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
        
        if(head){
            Node* newN = new Node;
            newN->bef = head;
            Node* curr = newN;
            Node* maxim = newN;
            
            while(curr->bef){
                if(curr->bef->value > maxim->bef->value)
                    maxim = curr;
                curr = curr->bef;
            }
            
            if(maxim == newN)
                head = head->bef;
            Node* temp = maxim->bef;
            maxim->bef = maxim->bef->bef;
            delete newN;
            delete temp;
            
            cout << "всё\n" << endl;
        } else {
            cout << " stack is empty";
        }
    }
    
    Stak draw(){
        Stak ret;
        
        
        Node* curr = head;
        
        while(curr){
            if(curr->value%2==0){
                ret.push(curr->value);
            }
            curr = curr->bef;
        }
        
        Node* curr2 = ret.head;
        
        while(curr2){
            cout << curr2->value << " ";
            curr2 = curr2->bef;
        }
        
        delete curr;
        delete curr2;
        return ret;
    }
    
    void printall(){
        Node* curr = head;
        
        while(curr){
            cout << curr->value << " ";
            curr = curr->bef;
        }
        
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
    srand(time(NULL));
    
    int iche, num;
    bool iswork = true;
    
    cout << "0. добавить число в стек\n 1. добавить случайное число в стек\n 2. посмотреть числа в стеке\n 3. удалить максимальное значение\n 4. чётное 5. выход\n\n";
    
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
                cout << "всё\n" << endl;
                break;
            }
            case 2:{
                bruh.printall();
                break;
            }
            case 3:{
                bruh.maximilian();
                break;
            }
            case 4:{
                bruh.draw();
                break;
            }
                
            case 5:{
                iswork = false;
            }
            default:
                break;
        }
    }
    return 0;
}
