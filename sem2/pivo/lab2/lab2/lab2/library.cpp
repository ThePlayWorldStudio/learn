#define _CRT_SECURE_NO_WARNINGS
#include "library.h"         

string readSets(const char* filename) {       // делит строку на элементы вектора через ,
    FILE* file = fopen(filename, "r"); 
    
    if (!file) {
        cout << "Ошибка открытия файла!\n";
        return NULL;
    }

    string content;
    char buffer[1024];

    while (fgets(buffer, sizeof(buffer), file)) {
        content += buffer;
    }

    fclose(file);
    return content;

}

int checkString(string sets){
    int size = sets.length();
    int openF=0;
    int closeF=0;
    int openS=0;
    int closeS=0;
    int numSets=0;

    for(int i = 0; i<size; i++){
        if(sets[i] == '{')      openF++;
        if(sets[i] == '}')      closeF++;
        if(sets[i] == '<')      openS++;
        if(sets[i] == '>')      closeS++;
	if(sets[i] == '\n') 	numSets++;

        if(sets[i]==' ')        return -1;
    }

    if(openF!=closeF || openS!=closeS)  return -1;

    return numSets;
}

vector<string> parseString(int num, string str){
	vector<string> sets;
	
	str.erase(0, 1);
	for(int i = 0; str[i]!='\0'; i++){
		if(str[i+1]=='\n' || str[i-1]=='\n')
			str.erase(i, 1);
	}


	char* temp = strtok(str.data(), "\n");
	while(temp){
		sets.push_back(temp);
		temp=strtok(NULL, "\n");
	}

	return sets;
}

vector<string> addSets(string str){
	vector<string> set;
	string temp;

	int setCount = 0;
	int tupeCount = 0;

	for(char c: str){
		if(c=='{'){
			setCount++;
			temp+=c;
		} else if (c=='}'){
			setCount--;
			temp+=c;
			if(setCount ==0){
				set.push_back(temp);
				temp.clear();
			}
		} 

		if(c=='<'){
			tupeCount++;
			temp+=c;
		} else if (c=='>'){
			tupeCount--;
			temp+=c;
			if(setCount == 0){
				set.push_back(temp);
				temp.clear();
			}
		} else if(c==',' && setCount == 0 && tupeCount == 0){
			if(!temp.empty()){
				set.push_back(temp);
				temp.clear();
			}
		} else {
			temp+=c;
		}
	}
	if(!temp.empty()){
		set.push_back(temp);
	}
	return set;
}

vector<string> cross(vector<string> set1, vector<string> set2){
	vector<string> cross;
	int num1 = set1.size();
	int num2 = set2.size();

	int eq = 0;

	for(int i = 0; i<num1; i++){
		for(int j = 0; j<num2; j++){
			if(set1[i][0]=='{' && set2[j][0]=='{'){
				if(set1[i].length()!=set2[j].length())
					continue;
				else{
					for(int k = 0; k<set1[i].length(); k++){
						for(int l = 0; l<set2[j].length(); l++){
							if(set1[i][k]=='{' || set1[i][k]==',' || set1[i][l]=='}')
								break;
							if(set1[i][k]==set2[j][l])
								eq = 1;
						}
						if(eq){
							cross.push_back(set1[i]);
							eq = 0;
						}
					}
				}
			}
		else if(!strcmp(set1[i].data(), set2[j].data()))
				eq = 1;
		}
		if(eq){
			cross.push_back(set1[i]);
			eq = 0;
		}
	}
	return cross;

}
