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
        if(last&&first){
            Node* temp = last;
            last = last->prev;
            last->next = NULL;
            delete temp;
            return 0;
        }
        else{
            cout << "stack is empty\n";
            return -1;
        }
    }
    
    int popfront(){
        if(first&&last){
            Node* temp = first;
            first = first->next;
            first->prev = NULL;
            delete temp;
            return 0;
        }
        else{
            cout << "stack is empty\n";
            return -1;
        }
    }
    
    int count(){
        int num = 0;
        Node* curr = first;
        while(curr){
            num++;
            curr = curr->next;
        }
        return num;
    }
    
    void printallfir(){
        Node* curr = first;
        while(curr){
            cout << curr->value << " ";
            curr = curr->next;
        }
        cout << endl;
    }
    
    void printalllast(){
        Node* curr = last;
        while(curr){
            cout << curr->value << " ";
            curr = curr->prev;
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
    
    void megaswap(){
        
        if(first){
            if(count()==1){
                return;
            }
            if(count()==2){
                Node* temp = first;
                first->prev = last;
                last->next = temp;
                first->next = NULL;
                last->prev = NULL;
                
                temp = first;
                first = last;
                last = temp;
                return ;
            }else{
                first->next->prev = last;
                last->prev->next = first;
                
                last->next = first->next;
                first->prev = last->prev;
                
                last->prev = NULL;
                first->next = NULL;
                
                Node* temp = first;
                first = last;
                last = temp;
                return;
            }
        }else{
            cout << "stack is empty!";
        }
        cout << endl;
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
    
    cout << "0: pushback \n 1: popback \n 2: pushfront \n 3: popfront \n 4: printall first -> last 7: printall last -> first \n 6: maximilian \n 7: exit \n";
    
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
                queue.printallfir();
                break;
            case 5:
                queue.printalllast();
                break;
            case 6:
                queue.maximilian();
                break;
            case 7:
                queue.megaswap();
                break;
            case 8:
                isWork = false;
                break;
                
            default:
                break;
        }
    }
    return 0;
}
