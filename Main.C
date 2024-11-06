#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <locale.h>
#include <time.h>
#include <math.h>
#include <ctype.h>
#include "UTILITIES.h"
#include "ARVORE.h"

int main() {

    setlocale(LC_ALL, "Portuguese");
    
    char opcao[3];
    int opcaoNum = 0;

    Arvore *arvore = criaArvore();

    do {
        do {
            system("cls");
            printf("\n\t\t1. Inserir os dados\n");
            printf("\t\t2. Alterar um dado\n");
            printf("\t\t3. Incluir novo funcionário\n");
            printf("\t\t4. Remover um funcionário\n");
            printf("\t\t5. Buscar as informações de um funcionário\n");
            printf("\t\t6. Buscar o funcionário mais novo e mais velho\n");
            printf("\t\t7. Buscar todos os funcionários de um cargo\n");
            printf("\t\t8. Sair\n");
            printf("\n\tOpção: ");
            fflush(stdin);
            fgets(opcao, sizeof(opcao), stdin);         //limpa o cache e coleta 3 digitos e apos transforma em int
            opcaoNum = atoi(opcao);                     
            if(!digitCheck(opcao) || outOfRange(opcaoNum,8,1))    {     //verifica se todos os caracteres sao numeros e se estao no intervalo correto
                system("cls");
                printf("\n\n\n\tErro! \t Digite uma opção válida!\n\n");
                system("pause");
            }
        }while(!digitCheck(opcao) || outOfRange(opcaoNum,8,1));

        system("cls");
        switch (opcaoNum) {
            case 1:
                FILE *ARQ;
                ARQ = fopen("Dados.txt", "r");
                if (ARQ == NULL) {
                    printf("\n\n\tErro ao abrir o arquivo\n\n");
                    system("pause");
                    break;
                }
                int numFuncionarios;
                fscanf(ARQ, "%d", &numFuncionarios);
                for (int i = 0; i < 2; i++) {
                    int matricula, idade;
                    char nome[40], cargo[25];
                    float salario;
                    fscanf(ARQ, "%d", &matricula);
                    fgets(nome, 40, ARQ);
                    fscanf(ARQ, "%d", &idade);
                    fgets(cargo, 25, ARQ);
                    fscanf(ARQ, "%f", &salario);
                    //insereArvore(arvore, matricula, nome, idade, cargo, salario);
                    printf("\n\n\tMATRICULA %d\n\tNOME %s\n\tIDADE %d\n\tCARGO %s\n\tSALARIO %.2f\n\n", matricula, nome, idade, cargo, salario);
                }

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
    } while (opcaoNum != 8);
}