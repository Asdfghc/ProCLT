#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <ctype.h>
#include "UTILITIES.h"
#include "ARVORE.h"

int main() {
    setlocale(LC_ALL, "Portuguese");
    
    char opcao[3];
    int opcaoNum = 0;

    char nome[40];
    char inputMatricula[6];
    int matricula;
    char inputIdade[4];
    int idade = 0;
    char cargo[25];
    char inputSalario[7];
    float salario = 0;

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
            fgets(opcao, sizeof(opcao), stdin);
            opcaoNum = atoi(opcao);                     
            if(!digitCheck(opcao)) {
                system("cls");
                printf("\n\n\tDigite um número!\n\n");
                system("pause");
            }
        }while(!digitCheck(opcao));

        system("cls");
        switch (opcaoNum) {
            case 1:
                FILE *ARQ;
                ARQ = fopen("Dados.txt", "r");
                if (ARQ == NULL) {
                    printf("\n\n\tErro ao abrir o arquivo...\n\n");
                    system("pause");
                    break;
                }
                int numFuncionarios;
                fscanf(ARQ, "%d", &numFuncionarios);
                for (int i = 0; i < numFuncionarios; i++) {
                    int matricula, idade;
                    char nome[40], cargo[25];
                    float salario;
                    fscanf(ARQ, "%d", &matricula);
                    fgets(nome, 40, ARQ);
                    fscanf(ARQ, "%d", &idade);
                    fgets(cargo, 25, ARQ);
                    fscanf(ARQ, "%f", &salario);
                    insereArvore(arvore, matricula, nome, idade, cargo, salario);
                }
                fclose(ARQ);
                printf("\n\n\tDados inseridos com sucesso...\n\n");
                //imprimeArvore(arvore, 1);
                system("pause");
                break;

            case 2:
                No* no;
                do {
                    printf("\n\t\tMatrícula do funcionário: ");
                    fflush(stdin);
                    fgets(inputMatricula, sizeof(inputMatricula), stdin);
                    matricula = atoi(inputMatricula);
                    if (outOfRange(matricula,9999,1000) || !digitCheck(inputMatricula))     printf("\n\n\tMatrícula inválida!\n\n");
                } while(outOfRange(matricula,9999,1000) || !digitCheck(inputMatricula));
                no = buscaArvore(arvore, matricula);
                if (no == NULL) {
                    printf("\n\n\tFuncionário não encontrado...\n\n");
                    system("pause");
                    break;
                }
                imprimeNo(no);

                printf("\n\n\t\t\tNome: ");
                fflush(stdin);
                fgets(nome, sizeof(nome), stdin);
                strcpy(no->nome, nome);

                do {
                    printf("\n\n\tIdade: ");
                    fflush(stdin);
                    fgets(inputIdade, sizeof(inputIdade), stdin);
                    idade = atoi(inputIdade);
                    if (outOfRange(idade,99,1) || !digitCheck(inputIdade))     printf("\n\n\tIdade inválida!\n\n");
                } while(outOfRange(idade,99,1) || !digitCheck(inputIdade));
                no->idade = idade;

                printf("\n\n\t\t\tCargo: ");
                fflush(stdin);
                fgets(cargo, sizeof(cargo), stdin);
                strcpy(no->cargo, cargo);

                do {
                    printf("\n\n\tSalário: ");      
                    fflush(stdin);
                    fgets(inputSalario, sizeof(inputSalario), stdin);
                    salario = atoi(inputSalario);
                    if (outOfRange(salario,999,1) || !digitCheck(inputSalario))     printf("\n\n\tSalário inválido!\n\n");
                } while(outOfRange(salario,999,1) || !digitCheck(inputSalario));
                no->salario = salario;

                printf("\n\n\tAlteração realizada com sucesso...\n\n");

                //memset(nome, 0, sizeof(nome));
                //memset(cargo, 0, sizeof(cargo));
                //idade = 0;
                //salario = 0;
                //matricula = 0;

                system("pause");
                break;

            case 3:
                do {
                    printf("\n\t\tMatrícula do funcionário: ");
                    fflush(stdin);
                    fgets(inputMatricula, sizeof(inputMatricula), stdin);
                    matricula = atoi(inputMatricula);
                    if (outOfRange(matricula,9999,1000) || !digitCheck(inputMatricula))     printf("\n\n\tMatrícula inválida!\n\n");
                } while(outOfRange(matricula,9999,1000) || !digitCheck(inputMatricula));


                printf("\n\n\t\t\tNome: ");
                fflush(stdin);
                fgets(nome, sizeof(nome), stdin);

                do {
                    printf("\n\n\tIdade: ");
                    fflush(stdin);
                    fgets(inputIdade, sizeof(inputIdade), stdin);
                    idade = atoi(inputIdade);
                    if (outOfRange(idade,99,1) || !digitCheck(inputIdade))     printf("\n\n\tIdade inválida!\n\n");
                } while(outOfRange(idade,99,1) || !digitCheck(inputIdade));
                

                printf("\n\n\t\t\tCargo: ");
                fflush(stdin);
                fgets(cargo, sizeof(cargo), stdin);
                

                do {
                    printf("\n\n\tSalário: ");   
                    fflush(stdin);
                    fgets(inputSalario, sizeof(inputSalario), stdin);
                    salario = atoi(inputSalario);
                    if (outOfRange(salario,99999,0) || !digitCheck(inputSalario))     printf("\n\n\tSalário inválido!\n\n");
                } while(outOfRange(salario,99999,0) || !digitCheck(inputSalario));
             

                insereArvore(arvore, matricula, nome, idade, cargo, salario);

                //memset(nome, 0, sizeof(nome));
                //memset(cargo, 0, sizeof(cargo));
                // idade = 0;
                //salario = 0;
                //matricula = 0;

                printf("\n\n\tFuncionário inserido com sucesso...\n\n");
                system("pause");
                break;

            case 4:
                do {
                    printf("\n\t\tMatrícula do funcionário: ");
                    fflush(stdin);
                    fgets(inputMatricula, sizeof(inputMatricula), stdin);
                    matricula = atoi(inputMatricula);
                    if (outOfRange(matricula,9999,1000) || !digitCheck(inputMatricula))     printf("\n\n\tMatrícula inválida!\n\n");
                } while(outOfRange(matricula,9999,1000) || !digitCheck(inputMatricula));
                if (removeArvore(arvore, matricula)) printf("\n\n\tFuncionário removido com sucesso...\n\n");
                system("pause");
                break;

            case 5:
                //No* no;
                do {
                    printf("\n\t\tMatrícula do funcionário: ");
                    fflush(stdin);
                    fgets(inputMatricula, sizeof(inputMatricula), stdin);
                    matricula = atoi(inputMatricula);
                    if (outOfRange(matricula,9999,1000) || !digitCheck(inputMatricula))     printf("\n\n\tMatrícula inválida!\n\n");
                } while(outOfRange(matricula,9999,1000) || !digitCheck(inputMatricula));
                no = buscaArvore(arvore, matricula);
                if (no == NULL) {
                    printf("\n\n\tFuncionário não encontrado...\n\n");
                    system("pause");
                    break;
                }
                imprimeNo(no);
                system("pause");
                break;

            case 6:
                break;

            case 7:
                break;

            case 8:
                //TODO: salvar no arquivo
                liberaArvore(arvore);
                printf("\n\n\tPrograma encerrado...\n\n");
                break;

            default:
                printf("\n\n\tDigite uma opção válida...\n\n");
                system("pause");
                break;
        }
    } while (opcaoNum != 8);
}