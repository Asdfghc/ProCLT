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
            printf("\t\t3. Incluir novo funcionario\n");
            printf("\t\t4. Remover um funcionario\n");
            printf("\t\t5. Buscar as informacoes de um funcionario\n");
            printf("\t\t6. Buscar o funcionario mais novo e mais velho\n");
            printf("\t\t7. Buscar todos os funcionarios de um cargo\n");
            printf("\t\t8. Imprimir a arvore de funcionarios\n");
            printf("\t\t9. Sair\n");
            printf("\n\tOpcao: ");
            fflush(stdin);
            fgets(opcao, sizeof(opcao), stdin);
            opcaoNum = atoi(opcao);
            if(!digitCheck(opcao)) {
                clearScreen();
                printf("\n\n\tDigite um numero!\n\n");
                pauseScreen();
            }
        }while(!digitCheck(opcao));

        clearScreen();
        switch (opcaoNum) {
            case 1:
                {
                    FILE *ARQ;
                    ARQ = fopen("Dados.txt", "r");
                    if (ARQ == NULL) {
                        printf("\n\n\tErro ao abrir o arquivo!\n\n");
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
                       fscanf(ARQ, "%d", &idade);
                       fgetc(ARQ);
                       fgets(cargo, 25, ARQ);
                       fscanf(ARQ, "%15s\n", salarioString);

                       salario = atof(salarioString);
                       arvore->raiz = inserirAVL(arvore->raiz, matricula, nome, idade, cargo, salario);
                    }

                    fclose(ARQ);
                    printf("\n\n\tDados inseridos com sucesso...\n\n");
                    pauseScreen();
                    break;
                }

            case 2:
                {
                    printf("\n\t\tMatricula do funcionario: ");
                    fflush(stdin);
                    fgets(inputMatricula, sizeof(inputMatricula), stdin);
                    matricula = atoi(inputMatricula);
                    if (outOfRange(matricula,9999,1000) || !digitCheck(inputMatricula)) {
                        printf("\n\n\tMatricula invalida!\n\n");
                        pauseScreen();
                        break;
                    }
                    no = buscaArvore(arvore, matricula);
                    if (no == NULL) {
                        printf("\n\n\tMatricula nao encontrada!\n\n");
                        pauseScreen();
                        break;
                    }
                    imprimeNo(no);

                    printf("\n\n\t\t\tNome: ");
                    fflush(stdin);
                    fgets(nome, sizeof(nome), stdin);
                    aumentaStringNome(nome);
                    strcpy(no->nome, nome);

                    do {
                        printf("\n\n\t\t\tIdade: ");
                        fflush(stdin);
                        fgets(inputIdade, sizeof(inputIdade), stdin);
                        idade = atoi(inputIdade);
                        if (outOfRange(idade,99,1) || !digitCheck(inputIdade))     printf("\n\n\tIdade invalida!\n\n");
                    } while(outOfRange(idade,99,1) || !digitCheck(inputIdade));
                    no->idade = idade;

                    printf("\n\n\t\t\tCargo: ");
                    fflush(stdin);
                    fgets(cargo, sizeof(cargo), stdin);
                    toUpperString(cargo);
                    aumentaStringCargo(cargo);
                    strcpy(no->cargo, cargo);

                    do {
                        printf("\n\n\t\t\tSalario: ");
                        fflush(stdin);
                        fgets(inputSalario, sizeof(inputSalario), stdin);
                        salario = atof(inputSalario);
                        if (outOfRange(salario,99999,1) || !digitCheck(inputSalario))     printf("\n\n\tSalario invalido!\n\n");
                    } while(outOfRange(salario,99999,1) || !digitCheck(inputSalario));
                    no->salario = salario;

                    printf("\n\n\tAlteracao realizada com sucesso...\n\n");
                    pauseScreen();
                    break;
                }

            case 3:
                {
                    do {
                        printf("\n\t\tMatricula do funcionario: ");
                        fflush(stdin);
                        fgets(inputMatricula, sizeof(inputMatricula), stdin);
                        matricula = atoi(inputMatricula);
                        if (outOfRange(matricula,9999,1000) || !digitCheck(inputMatricula))     printf("\n\n\tMatricula invalida!\n\n");
                        if(existeNaArvore(arvore,matricula)) printf("\n\n\tJa existe um funcionario com essa matricula\n\n");
                    } while(outOfRange(matricula,9999,1000) || !digitCheck(inputMatricula) || existeNaArvore(arvore,matricula));

                    printf("\n\n\t\t\tNome: ");
                    fflush(stdin);
                    fgets(nome, sizeof(nome), stdin);
                    aumentaStringNome(nome);

                    do {
                        printf("\n\n\t\t\tIdade: ");
                        fflush(stdin);
                        fgets(inputIdade, sizeof(inputIdade), stdin);
                        idade = atoi(inputIdade);
                        if (outOfRange(idade,99,1) || !digitCheck(inputIdade))     printf("\n\n\tIdade invalida!\n\n");
                    } while(outOfRange(idade,99,1) || !digitCheck(inputIdade));


                    printf("\n\n\t\t\tCargo: ");
                    fflush(stdin);
                    fgets(cargo, sizeof(cargo), stdin);
                    toUpperString(cargo);
                    aumentaStringCargo(cargo);



                    do {
                        printf("\n\n\t\t\tSalario: ");
                        fflush(stdin);
                        fgets(inputSalario, sizeof(inputSalario), stdin);
                        salario = atof(inputSalario);
                        if (outOfRange(salario,99999,0) || !digitCheck(inputSalario))     printf("\n\n\tSalario invalido!\n\n");
                    } while(outOfRange(salario,99999,0) || !digitCheck(inputSalario));


                    arvore->raiz = inserirAVL(arvore->raiz, matricula, nome, idade, cargo, salario);



                    printf("\n\n\tFuncionario inserido com sucesso...\n\n");
                    pauseScreen();
                    break;
                }

            case 4:
                {
                    printf("\n\t\tMatricula do funcionario: ");
                    fflush(stdin);
                    fgets(inputMatricula, sizeof(inputMatricula), stdin);
                    matricula = atoi(inputMatricula);
                    if (outOfRange(matricula,9999,1000) || !digitCheck(inputMatricula)) {
                        printf("\n\n\tMatricula invalida!\n\n");
                        pauseScreen();
                        break;
                    }
                    if(existeNaArvore(arvore,matricula)){
                        arvore->raiz = removerAVL(arvore->raiz, matricula);
                        printf("\n\n\tFuncionario removido com sucesso...\n\n");
                    }
                    else{
                        printf("\n\tMatricula nao encontrada!\n");
                    }
                    pauseScreen();
                    break;
                }

            case 5:
                {
                    printf("\n\t\tMatricula do funcionario: ");
                    fflush(stdin);
                    fgets(inputMatricula, sizeof(inputMatricula), stdin);
                    matricula = atoi(inputMatricula);
                    if (outOfRange(matricula,9999,1000) || !digitCheck(inputMatricula)) {
                        printf("\n\n\tMatricula invalida!\n\n");
                        pauseScreen();
                        break;
                    }
                    no = buscaArvore(arvore, matricula);
                    if (no == NULL) {
                        printf("\n\n\tMatricula nao encontrada!\n\n");
                        pauseScreen();
                        break;
                    }
                    imprimeNo(no);
                    pauseScreen();
                    break;
                }

            case 6:
                {
                    if (maiorIdadeArvore(arvore) != NULL) {
                        printf("\n\n\tFuncionario mais velho:\n");
                        imprimeNo(maiorIdadeArvore(arvore));
                    }
                    if (menorIdadeArvore(arvore) != NULL) {
                        printf("\n\n\tFuncionario mais novo:\n");
                        imprimeNo(menorIdadeArvore(arvore));
                    }
                    pauseScreen();
                    break;
                }

            case 7:
                {
                        printf("\n\t\tCargo do funcionario: ");
                        fflush(stdin);
                        fgets(cargo, sizeof(cargo), stdin);
                        toUpperString(cargo);
                        aumentaStringCargo(cargo);
                        clearScreen();
                        printf("\n\n\tFuncionarios com o cargo de %s: \n", cargo);
                        imprimeCargo(arvore, cargo);
                        pauseScreen();
                    break;
                }

            case 8:
                {
                    do {
                        clearScreen();
                        printf("\n\n\tComo deseja a impressao?\n");
                        printf("\t\t1. Pre-ordem\n");
                        printf("\t\t2. Em ordem\n");
                        printf("\t\t3. Pos-ordem\n");
                        printf("\n\tOpcao: ");
                        fflush(stdin);
                        fgets(opcao, sizeof(opcao), stdin);
                        opcaoNum = atoi(opcao);
                        if(!digitCheck(opcao) || outOfRange(opcaoNum,3,1)) {
                            clearScreen();
                            printf("\n\n\tDigite um numero valido!\n\n");
                            pauseScreen();
                        }

                    }while(!digitCheck(opcao) || outOfRange(opcaoNum,3,1));
                    clearScreen();
                    imprimeArvore(arvore, opcaoNum-1);
                    pauseScreen();
                    break;
                }

            case 9:
                {
                    FILE *arquivo = fopen("Dados.txt", "w");
                    if (arquivo == NULL) {
                        printf("\n\n\tErro ao abrir o arquivo para salvar os dados!\n\n");
                        break;
                    }

                    fprintf(arquivo, "%d\n", contarNos(arvore->raiz));
                    salvarArvore(arvore->raiz, arquivo);
                    fclose(arquivo);

                    liberaArvore(arvore);
                    printf("\n\n\tDados salvos e memoria liberada. Programa encerrado...\n\n");

                    break;
                }

                default: {
                    printf("\n\n\tDigite uma opcao valida!\n\n");
                    pauseScreen();
                    break;
                }
        }
    } while (opcaoNum != 9);
}
