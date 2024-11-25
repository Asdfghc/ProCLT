#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <locale.h>
#include <ctype.h>
#include "UTILITIES.h"
#include "ARVORE.h"

int main() {
    setlocale(LC_ALL, "Portuguese");
    
    char opcao[3];
    int opcaoNum = 0;

    char nome[41];
    char inputMatricula[6];
    int matricula;
    char inputIdade[4];
    int idade = 0;
    char cargo[26];
    char inputSalario[16];
    float salario = 0;

    Arvore *arvore = criaArvore();
    No* no;

    do {
        do {
            clearScreen();
            printf("\n\t\t1. Inserir os dados\n");
            printf("\t\t2. Alterar um dado\n");
            printf("\t\t3. Incluir novo funcionário\n");
            printf("\t\t4. Remover um funcionário\n");
            printf("\t\t5. Buscar as informações de um funcionário\n");
            printf("\t\t6. Buscar o funcionário mais novo e mais velho\n");
            printf("\t\t7. Buscar todos os funcionários de um cargo\n");
            printf("\t\t8. Imprimir a árvore de funcionários\n");
            printf("\t\t9. Sair\n");
            printf("\n\tOpção: ");
            fflush(stdin);
            fgets(opcao, sizeof(opcao), stdin);
            opcaoNum = atoi(opcao);                     
            if(!digitCheck(opcao)) {
                clearScreen();
                printf("\n\n\tDigite um número!\n\n");
                printf("Pressione Enter para continuar..."); 
                pauseScreen();
            }
        }while(!digitCheck(opcao));

        clearScreen();
        switch (opcaoNum) {
            case 1:
                FILE *ARQ;
                ARQ = fopen("Dados.txt", "r");
                if (ARQ == NULL) {
                    printf("\n\n\tErro ao abrir o arquivo!\n\n");
                    printf("Pressione Enter para continuar...");
                    pauseScreen();
                    break;
                }
                int numFuncionarios;
                fscanf(ARQ, "%d", &numFuncionarios);
                for (int i = 0; i < numFuncionarios; i++) {
                   char salarioString[16];
                   fscanf(ARQ, "%d", &matricula);
                   fgetc(ARQ);
                   fgets(nome, 40, ARQ);
                   nome[strcspn(nome, "\n")] = '\0';
                   fscanf(ARQ, "%d", &idade);
                   fgetc(ARQ);
                   fgets(cargo, 25, ARQ);
                   cargo[strcspn(cargo, "\n")] = '\0';           
                   fscanf(ARQ, "%15s\n", salarioString);     
                   
                   salario = atof(salarioString);
                   arvore->raiz = inserirAVL(arvore->raiz, matricula, nome, idade, cargo, salario);
                }

                fclose(ARQ);
                printf("\n\n\tDados inseridos com sucesso...\n\n");
                printf("Pressione Enter para continuar...");
                pauseScreen();
                break;

            case 2:
                do {
                    printf("\n\t\tMatrícula do funcionário: ");
                    fflush(stdin);
                    fgets(inputMatricula, sizeof(inputMatricula), stdin);
                    matricula = atoi(inputMatricula);
                    if (outOfRange(matricula,9999,1000) || !digitCheck(inputMatricula))     printf("\n\n\tMatrícula inválida!\n\n");
                    if(!existeNaArvore(arvore,matricula)) printf("\n\n\tNenhum funcionario com essa matricula\n\n");
                } while(outOfRange(matricula,9999,1000) || !digitCheck(inputMatricula) || !existeNaArvore(arvore,matricula));
                no = buscaArvore(arvore, matricula);
                if (no == NULL) {
                    printf("\n\n\tFuncionário não encontrado...\n\n");
                    printf("Pressione Enter para continuar..."); 
                    pauseScreen();
                    break;
                }
                imprimeNo(no);

                printf("\n\n\t\t\tNome: ");
                fflush(stdin);
                fgets(nome, sizeof(nome), stdin);
                nome[strcspn(nome, "\n")] = '\0';
                aumentaStringNome(nome);
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
                cargo[strcspn(cargo, "\n")] = '\0';
                aumentaStringCargo(cargo);
                strcpy(no->cargo, cargo);

                do {
                    printf("\n\n\tSalário: ");      
                    fflush(stdin);
                    fgets(inputSalario, sizeof(inputSalario), stdin);
                    salario = atoi(inputSalario);
                    if (outOfRange(salario,99999,1) || !digitCheck(inputSalario))     printf("\n\n\tSalário inválido!\n\n");
                } while(outOfRange(salario,99999,1) || !digitCheck(inputSalario));
                no->salario = salario;

                printf("\n\n\tAlteração realizada com sucesso...\n\n");

                printf("Pressione Enter para continuar..."); 
                pauseScreen();
                break;

            case 3:
                do {
                    printf("\n\t\tMatrícula do funcionário: ");
                    fflush(stdin);
                    fgets(inputMatricula, sizeof(inputMatricula), stdin);
                    matricula = atoi(inputMatricula);
                    if (outOfRange(matricula,9999,1000) || !digitCheck(inputMatricula))     printf("\n\n\tMatrícula inválida!\n\n");
                    if(!existeNaArvore(arvore,matricula)) printf("\n\n\tNenhum funcionario com essa matricula\n\n");
                } while(outOfRange(matricula,9999,1000) || !digitCheck(inputMatricula) || !existeNaArvore(arvore,matricula));

                printf("\n\n\t\t\tNome: ");
                fflush(stdin);
                fgets(nome, sizeof(nome), stdin);
                nome[strcspn(nome, "\n")] = '\0';
                aumentaStringNome(nome);


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
                cargo[strcspn(cargo, "\n")] = '\0';
                toUpperString(cargo); 
                aumentaStringCargo(cargo);
                
                

                do {
                    printf("\n\n\tSalário: ");   
                    fflush(stdin);
                    fgets(inputSalario, sizeof(inputSalario), stdin);
                    salario = atoi(inputSalario);
                    if (outOfRange(salario,99999,0) || !digitCheck(inputSalario))     printf("\n\n\tSalário inválido!\n\n");
                } while(outOfRange(salario,99999,0) || !digitCheck(inputSalario));
             

                arvore->raiz = inserirAVL(arvore->raiz, matricula, nome, idade, cargo, salario);

                printf("\n\n\tFuncionário inserido com sucesso...\n\n");
                printf("Pressione Enter para continuar..."); 
                pauseScreen();
                break;

            case 4:
                do {
                    printf("\n\t\tMatrícula do funcionário: ");
                    fflush(stdin);
                    fgets(inputMatricula, sizeof(inputMatricula), stdin);
                    matricula = atoi(inputMatricula);
                    if (outOfRange(matricula,9999,1000) || !digitCheck(inputMatricula))     printf("\n\n\tMatrícula inválida!\n\n");
                } while(outOfRange(matricula,9999,1000) || !digitCheck(inputMatricula));
                if(existeNaArvore(arvore,matricula)){
                    arvore->raiz = removerAVL(arvore->raiz, matricula); 
                    printf("\n\n\tFuncionário removido com sucesso...\n\n");
                }
                else{
                    printf("\n\tMatricula nao encontrada!\n");
                }
                printf("Pressione Enter para continuar..."); 
                pauseScreen();
                break;

            case 5:
                do {
                    printf("\n\t\tMatrícula do funcionário: ");
                    fflush(stdin);
                    fgets(inputMatricula, sizeof(inputMatricula), stdin);
                    matricula = atoi(inputMatricula);
                    if (outOfRange(matricula,9999,1000) || !digitCheck(inputMatricula))     printf("\n\n\tMatrícula inválida!\n\n");
                    if(!existeNaArvore(arvore,matricula)) printf("\n\n\tNenhum funcionario com essa matricula\n\n");
                } while(outOfRange(matricula,9999,1000) || !digitCheck(inputMatricula) || !existeNaArvore(arvore,matricula));
                no = buscaArvore(arvore, matricula);
                if (no == NULL) {
                    printf("\n\n\tFuncionário não encontrado!\n\n");
                    printf("Pressione Enter para continuar..."); 
                    pauseScreen();
                    break;
                }
                imprimeNo(no);
                printf("Pressione Enter para continuar...");
                pauseScreen();
                break;

            case 6:
                if (maiorIdadeArvore(arvore) != 0) {
                    printf("\n\n\tFuncionário mais velho: %d anos\n", maiorIdadeArvore(arvore));
                }
                if (menorIdadeArvore(arvore) != 0) {
                    printf("\n\n\tFuncionário mais novo: %d anos\n", menorIdadeArvore(arvore));
                }
                printf("Pressione Enter para continuar..."); 
                pauseScreen();
                break;

            case 7:
                    printf("\n\t\tCargo do funcionário: ");
                    fflush(stdin);
                    fgets(cargo, sizeof(cargo), stdin);
                    cargo[strcspn(cargo, "\n")] = '\0';
                    toUpperString(cargo);   
                    aumentaStringCargo(cargo);
                    clearScreen();
                    printf("\n\n\tFuncionários com o cargo de %s: \n", cargo);
                    imprimeCargo(arvore, cargo);
                    printf("Pressione Enter para continuar..."); 
                    pauseScreen();
                break;

            case 8:
                do {
                    clearScreen();
                    printf("\n\n\tComo deseja a impressão?\n");
                    printf("\t\t1. Pré-ordem\n");
                    printf("\t\t2. Em ordem\n");
                    printf("\t\t3. Pós-ordem\n");
                    printf("\n\tOpção: ");
                    fflush(stdin);
                    fgets(opcao, sizeof(opcao), stdin);
                    opcaoNum = atoi(opcao);
                    if(!digitCheck(opcao) || outOfRange(opcaoNum,3,1)) {
                        clearScreen();
                        printf("\n\n\tDigite um número válido!\n\n");
                        printf("Pressione Enter para continuar..."); 
                        pauseScreen();
                    }

                }while(!digitCheck(opcao) || outOfRange(opcaoNum,3,1));
                clearScreen();
                imprimeArvore(arvore, opcaoNum-1);
                printf("Pressione Enter para continuar..."); 
                pauseScreen();
                break;
            
            case 9:
                FILE *arquivo = fopen("Dados.txt", "w");
                if (arquivo == NULL) {
                    printf("\n\n\tErro ao abrir o arquivo para salvar os dados!\n\n");
                    break;
                }

                fprintf(arquivo, "%d\n", contarNos(arvore->raiz));
                salvarArvore(arvore->raiz, arquivo);              
                fclose(arquivo);                                  

                liberaArvore(arvore);                             
                printf("\n\n\tDados salvos e memória liberada. Programa encerrado...\n\n");
                
                break;
            case 10: 
                if (estaBalanceada(arvore->raiz)) {
                    printf("\n\n\tA árvore está balanceada.\n\n");
                } else {
                    printf("\n\n\tA árvore NÃO está balanceada.\n\n");
                }
                printf("Pressione Enter para continuar...");
                getchar();
                pauseScreen();
                break;
            default:
                printf("\n\n\tDigite uma opção válida!\n\n");
                printf("Pressione Enter para continuar..."); 
                pauseScreen();
                break;
        }
    } while (opcaoNum != 9);
}