#ifndef UTILITIES_H_INCLUDED
#define UTILITIES_H_INCLUDED

bool digitCheck(char key[]) {
    for (unsigned int i = 0; i < strlen(key); i++)
    {
        if(!isdigit(key[i]) && key[i]!='\n')  return false;
    }
    return true;
}

bool outOfRange(int number, int max, int min) {
    if(max<number || min>number)    return true;
    return false;
}

void aumentaString (char str[26]){
    int tamanho = 24; 
    int len = strlen(str);

    for (int i = len-1; i >= 0; i--) {
        str[i + 1] = str[i];
    }
    str[0] = ' ';
    
    for(int i = len; i < tamanho; i++){
        str[i] = ' ';
    }
    str[tamanho] = '\0';
}

#endif //UTILITIES_H_INCLUDED