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

#endif //UTILITIES_H_INCLUDED