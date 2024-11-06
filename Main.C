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
                    printf("\n\n\tErro ao abrir o arquivo\n\n");
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
                printf("\n\n\tDados inseridos com sucesso\n\n");
                //imprimeArvore(arvore, 1);
                system("pause");
                break;

            case 2:
                No* no;
                no = buscaArvore(arvore, 4811); //TODO: mudar para input
                if (no == NULL) {
                    printf("\n\n\tFuncionário não encontrado\n\n");
                    system("pause");
                    break;
                }
                imprimeNo(no);
                printf("\n\n\tDigite o novo nome: ");
                //TODO: fazer os inputs

                strcpy(no->nome, "Novo Nome"); //TODO: mudar para input
                no->idade = 25; //TODO: mudar para input
                strcpy(no->cargo, "Novo Cargo"); //TODO: mudar para input
                no->salario = 2500.00; //TODO: mudar para input
                printf("\n\n\tAlteração realizada com sucesso\n\n");
                system("pause");
                break;

            case 3:
                insereArvore(arvore, 4811, "Novo Funcionário", 25, "Novo Cargo", 2500.00); //TODO: mudar para input
                printf("\n\n\tFuncionário inserido com sucesso\n\n");
                system("pause");
                break;

            case 4:
                if (removeArvore(arvore, 4811)) printf("\n\n\tFuncionário removido com sucesso\n\n"); //TODO: mudar para input
                system("pause");
                break;

            case 5:
                //No* no;
                no = buscaArvore(arvore, 4811); //TODO: mudar para input
                if (no == NULL) {
                    printf("\n\n\tFuncionário não encontrado\n\n");
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
                printf("\n\n\tPrograma encerrado\n\n");
                break;

            default:
                printf("\n\n\t Digite uma opção válida\n\n");
                system("pause");
                break;
        }
    } while (opcaoNum != 8);
}