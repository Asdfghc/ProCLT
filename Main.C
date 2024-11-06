#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <locale.h>
#include <time.h>
#include <math.h>

int main() {

    setlocale(LC_ALL, "Portuguese");
    
    int opcaoNum = 0;

     while (opcaoNum != 7) {

            system("cls");
            printf("\n\t\t1. a\n");
            printf("\t\t2. a\n");
            printf("\t\t3. a\n");
            printf("\t\t4. a\n");
            printf("\t\t5. a\n");
            printf("\t\t6. a\n");
            printf("\t\t7. a\n");
            printf("\n\tOpção: ");

        system("cls");
        switch (opcaoNum) {
            case 1:
                break;

            case 2:
                break;

            case 3:
                break;

            case 4:
                break;
            case 5:
                break;
            case 6:
                break;
            case 7:
                break;
            case 8:
                break;
            default:
                printf("\n\n\t Digite uma opção válida\n\n");
                system("pause");
                break;
        }
    }
}