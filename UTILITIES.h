#ifndef UTILITIES_H_INCLUDED
#define UTILITIES_H_INCLUDED

void clearScreen(){
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void pauseScreen(){
    #ifdef _WIN32
        system("pause");
    #else
        getchar();
    #endif
}

bool digitCheck(char key[]) {
    for (unsigned int i = 0; i < strlen(key); i++)
    {
        if(!isdigit(key[i]) && key[i]!='\n' && key[i]!=',')  return false;
    }
    return true;
}

bool outOfRange(int number, int max, int min) {
    if(max<number || min>number)    return true;
    return false;
}

void aumentaStringCargo (char str[26]){
    int tamanho = 24; 
    size_t len = strlen(str);

    
    for(int i = len; i < tamanho; i++){
        str[i] = ' ';
    }
    str[tamanho] = '\0';
}

void aumentaStringNome (char str[41]){
    int tamanho = 39; 
    size_t len = strlen(str);

    
    for(int i = len; i < tamanho; i++){
        str[i] = ' ';
    }
    str[tamanho] = '\0';
}

void toUpperString(char* str){
    for(int i=0; str[i]!='\0';i++){
        str[i]=toupper((unsigned char) str[i]);
    }
}

#endif //UTILITIES_H_INCLUDED