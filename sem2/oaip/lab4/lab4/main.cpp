#include <iostream>

using namespace std;

struct Node{
    int value;
    Node* prev = NULL;
    Node* next = NULL;
};

class Queue: public Node{
    
    Node* first = NULL;
    Node* last = NULL;
    
    void pushback(int data){
        Node* nw = new Node();
        nw->value = data;
        nw->prev = last;
        last = nw;
    }
    
    void pushfront(int data){
        Node* nw = new Node();
        nw->value = data;
        nw->next = first;
        first = nw;
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
            first = first->next;
            delete temp;
            return 0;
        }
        else{
            cout << "stack is empty\n";
            return -1;
        }
    }
    
};

int main() {
    
    return 0;
}
