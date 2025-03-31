#include <iostream>

using namespace std;

struct Node{
    int value;
    Node* prev = NULL;
    Node* next = NULL;
};

class Queue: public Node{
    
private:
    Node* first = NULL;
    Node* last = NULL;
    
public:
    void pushback(int data){
        Node* nw = new Node();
        nw->value = data;
        
        if(!first){
            first = nw;
            last = nw;
            return;
        }
        
        nw->next = first;
        first->prev = nw;
        first = nw;
    }
    
    void pushfront(int data){
        Node* nw = new Node();
        nw->value = data;
        
        if(!last){
            first = nw;
            last = nw;
            return;
        }
        
        nw->prev = last;
        last->next = nw;
        last = nw;
    }
    
    int popback(){
        if(last){
            Node* temp = last;
            last = last->prev;
            delete temp;
            return 0;
        }
        else{
            cout << "stack is empty\n";
            return -1;
        }
    }
    
    int popfront(){
        if(first){
            Node* temp = first;
            first = first->prev;
            delete temp;
            return 0;
        }
        else{
            cout << "stack is empty\n";
            return -1;
        }
    }
    
    void printall(){
        Node* curr = first;
        while(curr){
            cout << curr->value << " ";
            curr = curr->next;
        }
        cout << endl;
    }
    
    void maximilian(){
        
        if(last){
            Node* curr = first;
            Node* maxim = first;
            
            while(curr){
                if(curr->value > maxim->value)
                    maxim = curr;
                curr = curr->next;
            }
            
            if(maxim != first)  maxim->prev->next=maxim->next;
            else first=maxim->next;
               
            if(maxim != last) maxim->next->prev=maxim->prev;
            else last=maxim->prev;
        
            delete maxim;
            return;
            
            cout << "всё\n" << endl;
        } else {
            cout << " stack is empty";
        }
    }
    
    ~Queue(){
        while(last){
            popback();
        }
    }
    
};

int main() {
    
    srand(time(NULL));
    
    Queue queue;
    int iche, value;
    bool isWork = true;
    
    while(isWork){
        
        cin >> iche;
        
        switch (iche){
            case 0:
                queue.pushback(rand()%100);
                break;
                
            case 1:
                queue.popback();
                break;
                
            case 2:
                queue.pushfront(rand()%100);
                break;
                
            case 3:
                queue.popfront();
                break;
            
            case 4:
                queue.printall();
                break;
                
            case 5:
                queue.maximilian();
                break;
            case 6:
                isWork = false;
                break;
                
            default:
                break;
        }
    }
    return 0;
}
