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
    int matricula = 0;
    int idade = 0;
    char cargo[25];
    float salario = 0;

    Arvore *arvore = criaArvore();

    do {
        do {
            system("cls");
            printf("\n \t \t 1. Inserir os dados \n");
            printf("\t \t 2. Alterar um dado \n");
            printf("\t \t 3. Incluir novo funcionário \n");
            printf("\t \t 4. Remover um funcionário \n");
            printf("\t \t 5. Buscar as informações de um funcionário \n");
            printf("\t \t 6. Buscar o funcionário mais novo e mais velho \n");
            printf("\t \t 7. Buscar todos os funcionários de um cargo \n");
            printf("\t \t 8. Sair \n");
            printf("\n \t Opção: ");
            fflush(stdin);
            fgets(opcao, sizeof(opcao), stdin);
            opcaoNum = atoi(opcao);                     
            if(!digitCheck(opcao)) {
                system("cls");
                printf("\n \n \t Digite um número! \n \n");
                system("pause");
            }
        }while(!digitCheck(opcao));

        system("cls");
        switch (opcaoNum) {
            case 1:
                FILE *ARQ;
                ARQ = fopen("Dados.txt", "r");
                if (ARQ == NULL) {
                    printf("\n \n \t Erro ao abrir o arquivo... \n \n");
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
                printf("\n \n \t Dados inseridos com sucesso... \n \n");
                //imprimeArvore(arvore, 1);
                system("pause");
                break;

            case 2:
                No* no;
                printf("\n \t \t Matricula do funcionario: ");
                if(sizeof(matricula)>4){
                    printf("\n \n \t Matricul Invlida... \n \n");
                }
                scanf("%d", & matricula);
                no = buscaArvore(arvore, matricula);
                if (no == NULL) {
                    printf("\n \n \t Funcionário não encontrado... \n \n");
                    system("pause");
                    break;
                }
                imprimeNo(no);

                printf("\n \n \t \t \t Nome: ");
                scanf("%s", nome);
                strcpy(no->nome, nome);

                printf("\n \n \t \t \t Idade: ");
                scanf("%d", idade);
                if(idade > 99){
                    printf("\n \n \t \t Idadade Invalida...");
                }
                no->idade = idade;

                printf("\n \n \t \t \t Cargo: ");
                scanf("%d", cargo);
                strcpy(no->cargo, cargo);

                printf("\n \n \t \t \t Slario: ");
                scanf("%.2f", salario);
                no->salario = salario;

                printf("\n \n \t Alteração realizada com sucesso... \n \n");

                memset(nome, 0, sizeof(nome));
                memset(cargo, 0, sizeof(cargo));
                idade = 0;
                salario = 0;
                matricula = 0;

                system("pause");
                break;

            case 3:
                printf("\n \n \t \t Matricula do funcionario: ");
                scanf("%d", & matricula);
                if(sizeof(matricula)>4){
                    printf("\n \n \t Matricul Invlida... \n \n");
                }
                no->matricula -  matricula;

                printf("\n \n \t \t \t Nome: ");
                scanf("%s", nome);
                strcpy(no->nome, nome);

                printf("\n \n \t \t \t Idade: ");
                scanf("%d", idade);
                if(idade > 99){
                    printf("\n \n \t \t Idadade Invalida...");
                }
                no->idade = idade;

                printf("\n \n \t \t \t Cargo: ");
                scanf("%d", cargo);
                strcpy(no->cargo, cargo);

                printf("\n \n \t \t \t Slario: ");
                scanf("%.2f", salario);
                no->salario = salario;

                insereArvore(arvore, matricula, nome, idade, cargo, salario);

                memset(nome, 0, sizeof(nome));
                memset(cargo, 0, sizeof(cargo));
                idade = 0;
                salario = 0;
                matricula = 0;

                printf("\n \n \t Funcionário inserido com sucesso... \n \n");
                system("pause");
                break;

            case 4:
                printf("\n \n \t \t Matricula do funcionario: ");
                scanf("%d", & matricula);
                if(sizeof(matricula)>4){
                    printf("\n \n \t Matricul Invlida... \n \n");
                }
                if (removeArvore(arvore, matricula)) printf("\n \n \t Funcionário removido com sucesso...\n \n");
                system("pause");
                break;

            case 5:
                //No* no;
                no = buscaArvore(arvore, matricula);
                if (no == NULL) {
                    printf("\n \n \t Funcionário não encontrado... \n \n");
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
                printf("\n \n \t Programa encerrado... \n \n");
                break;

            default:
                printf("\n \n \t Digite uma opção válida... \n \n");
                system("pause");
                break;
        }
    } while (opcaoNum != 8);
}