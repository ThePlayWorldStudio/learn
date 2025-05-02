#include <iostream>

using namespace std;

int checkMath(char s){
    return s == '+' || s == '-' || s == '/' || s == '*';
}

template <typename T>
class Stak{
private:
    struct Node{
        T value;
        Node* bef = NULL;
    };
public:
    Node* head = NULL;
    

    void push(T data){
        Node* nw = new Node();
        nw->value = data;
        nw->bef = head;
        head = nw;
    }
    
    T peek(){
        if(head!=NULL)
            return head->value;
        else{
            return 1;
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
            return 1;
        }
    }
    
    int isExists(){
        if(head) return 1;
        else return 0;
    }
 
    ~Stak(){
        while (head) {
            pop();
        }
    }
    
};

class OPZ: Stak<char>{
public:
    Stak<char> postfix;
    Stak<char> temp;
    char postf[100];
    char* numsName;
    float* nums;
    int coun = 0;
    char inf[100];
    float answer;
    
public:
    
    void init(char* infix){
        strcpy(inf, infix);
    }
    
    void get_opz(){
        for(int i = 0; inf[i] != '\0'; i++){
            if(inf[i]=='('){
                postfix.push(inf[i]);
                continue;
            }
            
            if(inf[i]==')'){
                while (postfix.peek()!='(') {
                    temp.push(postfix.peek());
                    postfix.pop();
                }
                postfix.pop();
            }
            
            if ((inf[i] >= 'a' && inf[i] <= 'z')||(inf[i] >= 'A' && inf[i] <= 'Z' ))
                temp.push(inf[i]);
            
            if(checkMath(inf[i])){
                while(postfix.isExists() && prop(inf[i]) <= prop(postfix.peek())){
                    temp.push(postfix.peek());
                    postfix.pop();
                }
                postfix.push(inf[i]);
            }
                
                
        }
        
        while(postfix.isExists()){
            temp.push(postfix.peek());
            postfix.pop();
        }
        
        while(temp.isExists()){
//            if(temp.peek() != '('){
                postfix.push(temp.peek());
                temp.pop();
//            } else {
//                temp.pop();
//            }
        }
        
        toString(postf);
        
        numsName = new char[coun];
        nums = new float[coun];
        
        
        
        print(postf);
        
        int i = 0;
        int it = 0;
        bool flag = 1;
        
        long int count = strlen(postf);
        
        while(i<count){
            if((postf[i]>='a' && postf[i]<='z') || (postf[i]>='A' && postf[i]<='Z')){
                if(i==0){
                    numsName[it] = postf[i];
                    it++;
                    i++;
                    continue;
                }
                for(int g = 0; numsName[g]!='\0'; g++){
                    if(numsName[g]==postf[i]){
                        flag = 0;
                    }
                    
                }
                if(flag){
                    numsName[it] = postf[i];
                    it++;
                }
            }
            i++;
            flag = 1;
        }
        
        
        getNums(numsName);
        
        answer = calc(nums, numsName, postf);
        
        
    }
    
    int isMath(char s){
        return s == '+' || s == '-' || s == '/' || s == '*' || s == '(' || s == ')';
    }
    
    void toString(char* string){
        int i = 0;
        
        while(postfix.isExists()){
            postf[i] = postfix.peek();
            postfix.pop();
            i++;
        }
        postf[i] = '\0';
    }
    
    void getNums(char* names){
        float iche;
        
        for(int i = 0; names[i]!='\0'; i++){
            cout << "введите " << names[i] << endl;
            cin >> iche;
            nums[i] = iche;
        }
    }
    
    float calc(float * nums, char* names, char* posfix){
        float answ, x, y;
        Stak<float> operations;
        
        if((((posfix[0]<'a' && posfix[0]>'z') || (posfix[0]<'A' && posfix[0]>'Z')) && ((posfix[1]>='a' && posfix[1]>'z') || (posfix[1]<'A' && posfix[1]>'Z')))) return -1;
        
        for(int i = 0; posfix[i] != '\0'; i++){
            if((posfix[i]>='a' && posfix[i]<='z') || (posfix[i]>='A' && posfix[i]<='Z')){
                operations.push(nums[ind(posfix[i], numsName)]);
            } else {
                x = operations.peek();
                operations.pop();
                y = operations.peek();
                operations.pop();
                switch (posfix[i]) {
                    case '+':
                        operations.push(x+y);
                        break;
                    case '-':
                        operations.push(y-x);
                        break;
                    case '*':
                        operations.push(x*y);
                        break;
                    case '/':
                        operations.push(y/x);
                        break;
                    default:
                        break;
                }
            }
        }
        answ = operations.peek();
        return answ;
    }
    
    int prop(char symb){
        switch (symb) {
            case ('('): return 1;
            case('-'): case('+'): return 2;
            case('*'): case('/'): return 3;
            case('^'): return 4;
        }
        return 0;
    }
    
    int ind(char a, char* mass){
        for(int i = 0; mass[i]!='\0'; i++){
            if(mass[i]==a) return i;
        }
        return 0;
    }
    
    void print(char* string){
        cout << string << endl;
    }
    
    ~OPZ(){
        delete [] numsName;
        delete [] nums;
    }
    
};

int isLetter(char s){
    if((s>='a' && s<='z') || (s>='A' && s<='Z')){
        return 1;
    }
    return 0;
}

int main() {
    char* infix = new char[100];
    OPZ opz;
    int check = 1;
    int flag = 0;
    int flag2 = 1;
    int left = 0;
    int right = 0;
    
    while(check){
//        cin.ignore();
        cin.getline(infix, 100);
        long int size = strlen(infix);
        check = 0;
        for(int i = 0; i<size-1; i++){
            if( (isLetter(infix[i]) && isLetter(infix[i+1])) || (checkMath(infix[i]) && checkMath(infix[i+1])) || (isLetter(infix[i]) && infix[i+1]=='(') || (infix[i]==')' && isLetter(infix[i+1])) || (infix[i]=='(' && infix[i+1]==')') || (infix[i]==')' && infix[i+1]=='(') ) {
                flag = 1;
                break;
            }
            if(!isLetter(infix[i]) && !opz.isMath(infix[i])){
                flag = 1;
                break;
            }
                
        }
        for(int i = 0; i<size; i++){
            if(infix[i] == '('){
                for(int j = i; j < size; j++){
                    if(infix[j]==')'){
                        flag2 = 0;
                        break;
                    }
                }
                left++;
            }
            if(infix[i]==')'){
                right++;
            }
        }
        if(((flag || !flag2) && right==0) || checkMath(infix[size-1])){
            check = 1;
            flag = 0;
            flag2 = 1;
            right = 0;
            left = 0;
            cout << "retry\n";
        }
        if(((flag || flag2 || (right!=left)) && right!=0) || checkMath(infix[size-1])){
            check = 1;
            flag = 0;
            flag2 = 1;
            right = 0;
            left = 0;
            cout << "retry\n";
        }
    }
    
    opz.init(infix);
    opz.get_opz();
    cout << opz.answer << endl;
    
    delete [] infix;
    return 0;
}
