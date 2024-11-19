#ifndef UTILITIES_H_INCLUDED
#define UTILITIES_H_INCLUDED

/* FUNCOES AUXILIARES

bool digitCheck(char key[])     RETORNA TRUE SE NA STRING SÓ CONTER NUMEROS

bool outOfRange(int number, int max, int min)     RETORNA TRUE SE O NUMERO ESTIVER FORA DO INTERVALO

*/

bool digitCheck(char key[]) {
    for (unsigned int i = 0; i < strlen(key); i++)
    {
        if(!isdigit(key[i]) && key[i]!='\n')  return false;     //roda por toda a string verificando se o caracter é digito
    }
    return true;
}

bool outOfRange(int number, int max, int min) {
    if(max<number || min>number)    return true;
    return false;
}

void aumenta_string (char str[26]){
    int tamanho = 26; 
    int len = strlen(str);
    if (len > 0 && str[len - 1] == '\n') {
        str[len - 1] = '\0';
         len--;
    }
    if(len < tamanho){    
        for(int i = len; i < tamanho; i++){
            str[i] = ' ';
        }
        str[tamanho - 1] = '\0';
    }
}

#endif //UTILITIES_H_INCLUDED