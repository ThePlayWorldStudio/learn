#define _CRT_SECURE_NO_WARNINGS
#include "library.h"         

string readSets(const char* filename) { 
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
    stack<char> skob;

    for(int i = 0; i<size; i++){
        if(sets[i] == '{')      openF++;
        if(sets[i] == '}')      closeF++;
        if(sets[i] == '<')      openS++;
        if(sets[i] == '>')      closeS++;
	if(sets[i] == '\n') 	numSets++;

        if(sets[i]==' ')        return -1;
    }

    if(openF!=closeF || openS!=closeS)  return -1;

    for(int i = 0; i<size; i++){
	    if(sets[i]=='{' || sets[i]=='<'){
		    skob.push(sets[i]);
	    } else if(sets[i]=='}' || sets[i]=='>'){
		    if(skob.empty()) return -1;
		    char top = skob.top();
		    if((sets[i]=='}' && top!='{') || (sets[i]=='>' && sets[i]=='<')) return -1;
		    skob.pop();
	    } else if(sets[i]==','){
		    if(i==0 || i==sets.length()-1 || sets[i-1]==','|| sets[i+1]==','){
			    return -1;
		    }
	    }
    }

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
    int tupleCount = 0;

    for(char c : str){
        if(c == '{') {
            setCount++;
        } else if (c == '}') {
            setCount--;
        } else if(c == '<') {
            tupleCount++;
        } else if (c == '>') {
            tupleCount--;
        }

        if (c == ',' && setCount == 0 && tupleCount == 0) {
            // Разделяем элемент только если запятая ВНЕ множества/кортежа
            if (!temp.empty()) {
                set.push_back(temp);
                temp.clear();
            }
        } else {
            temp += c;
        }
    }

    if (!temp.empty()) {
        set.push_back(temp);
    }
    
    return set;
}


string sortSet(string& input) {
    vector<string> elements;
    string temp;
    int curlyBrackets = 0;
    int angleBrackets = 0;

    for (char c : input) {
        if (c == '{') {
            curlyBrackets++;
        } else if (c == '}') {
            curlyBrackets--;
        } else if (c == '<') {
            angleBrackets++;
        } else if (c == '>') {
            angleBrackets--;
        }

        temp += c;

        if ((c == '}' && curlyBrackets == 0) || (c == ',' && curlyBrackets == 0 && angleBrackets == 0)) {
            if (!temp.empty()) {
                elements.push_back(temp);
                temp.clear();
            }
        }
    }

    if (!temp.empty()) {
        elements.push_back(temp);
    }

    // Сортируем только множества `{}`, но НЕ затрагиваем `< >`
    for (auto& elem : elements) {
        if (elem.front() == '{' && elem.back() == '}') {
            vector<string> setElements;
            string innerTemp;
            int innerCurlyBrackets = 0;

            for (char c : elem) {
                if (c == '{') innerCurlyBrackets++;
                if (c == '}') innerCurlyBrackets--;

                innerTemp += c;

                if ((c == '}' && innerCurlyBrackets == 0) || (c == ',' && innerCurlyBrackets == 0)) {
                    setElements.push_back(innerTemp);
                    innerTemp.clear();
                }
            }

            if (!innerTemp.empty()) {
                setElements.push_back(innerTemp);
            }

            sort(setElements.begin(), setElements.end());

            elem = "{";
            for (size_t i = 0; i < setElements.size(); i++) {
                if (i > 0) elem += ",";
                elem += setElements[i];
            }
            elem += "}";
        }
    }

    // Собираем результат
    string result;
    for (const auto& elem : elements) {
        if (!result.empty()) result += ",";
        result += elem;
    }

    return result;
}




vector<string> cross(vector<string> set1, vector<string> set2){
	vector<string> cross;
	int num1 = set1.size();
	int num2 = set2.size();

	for(int i = 0; i<num1; i++){
		cout << set1[i] << "i \n";
	}
	
	for(int j = 0; j<num2; j++){
		cout << set2[j] << "i \n";
	}

	for(int i = 0; i<num1; i++){
		for(int j =  0; j<num2; j++){
			if(set1[i].front() == '{' || set1[i].front()=='<'){
				set1[i] = sortSet(set1[i]);
			}

			if(set2[j].front() == '{' || set2[j].front()=='<'){
				set2[j] = sortSet(set2[j]);
			}

			if(!strcmp(set1[i].data(), set2[j].data()))
				cross.push_back(set1[i]);
		}
	}
	return cross;
}
