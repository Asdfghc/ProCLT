#ifndef ARVORE_H_INCLUDED
#define ARVORE_H_INCLUDED

typedef struct No {
    int matricula, idade;
    char nome[41], cargo[26];
    float salario;
    struct No *esq, *dir;
} No;

typedef struct Arvore {
    No *raiz;
} Arvore;

Arvore* criaArvore() {
    Arvore *arvore = (Arvore*) malloc(sizeof(Arvore));
    arvore -> raiz = NULL;
    return arvore;
}

void insereArvore(Arvore* arvore, int matricula, char nome[40], int idade, char cargo[25], float salario) {
    No* novo = (No*) malloc(sizeof(No));
    novo -> matricula = matricula;
    novo -> idade = idade;
    strcpy(novo -> nome, nome);
    strcpy(novo -> cargo, cargo);
    novo -> salario = salario;
    novo -> esq = NULL;
    novo -> dir = NULL;
    if (arvore->raiz == NULL) {
        arvore -> raiz = novo;
    }
    else {
        int flag = 0;
        No* pai = arvore -> raiz;
        while (flag != 1) {
            if (matricula > pai->matricula) {
                if (pai->dir != NULL) {
                    pai = pai -> dir;
                }
                else {
                    pai -> dir = novo;
                    flag = 1;
                }
            }
            else {
                if (pai->esq != NULL) {
                    pai = pai -> esq;
                }
                else {
                    pai -> esq = novo;
                    flag = 1;
                }
            }
        }
    }
}

void imprimeNo(No* no) {
    printf("Matricula: %d\nNome:%s\nIdade: %d\nCargo:%s\nSalario: %.2f\n\n", no -> matricula, no -> nome, no -> idade, no -> cargo, no -> salario);
}

void imprimeSubArvore(No* no, int tipo) {
    if (tipo == 0) imprimeNo(no);
    if (no->dir != NULL) imprimeSubArvore(no -> dir, tipo);
    if (tipo == 1) imprimeNo(no);
    if (no->esq != NULL) imprimeSubArvore(no -> esq, tipo);
    if (tipo == 2) imprimeNo(no);
}

void imprimeArvore(Arvore* arvore, int tipo) {
    if (arvore -> raiz == NULL) {
        printf("Arvore vazia\n");
        return;
    }
    printf("\n");
    imprimeSubArvore(arvore -> raiz, tipo);
    printf("\n");
}

No* maiorIdadeSubArvore(No* no, int maiorIdade) {
    if (no->dir == NULL && no->esq != NULL) {
        if (maiorIdadeSubArvore(no -> esq, maiorIdade)->idade > maiorIdade) {
            return maiorIdadeSubArvore(no -> esq, maiorIdade);
        }
    }
    if (no->esq == NULL && no->dir != NULL) {
        if (maiorIdadeSubArvore(no -> dir, maiorIdade)->idade > maiorIdade) {
            return maiorIdadeSubArvore(no -> dir, maiorIdade);
        }
    }
    if (no->esq != NULL && no->dir != NULL) {
        if (maiorIdadeSubArvore(no -> dir, maiorIdade)->idade > maiorIdade) {
            if (maiorIdadeSubArvore(no -> esq, maiorIdade)->idade > maiorIdade) {
                if (maiorIdadeSubArvore(no -> dir, maiorIdade)->idade > maiorIdadeSubArvore(no -> esq, maiorIdade)->idade) {
                    return maiorIdadeSubArvore(no -> dir, maiorIdade);
                } else {
                    return maiorIdadeSubArvore(no -> esq, maiorIdade);
                }
            } else {
                return maiorIdadeSubArvore(no -> dir, maiorIdade);
            }
        } else {
            if (maiorIdadeSubArvore(no -> esq, maiorIdade)->idade > maiorIdade) {
                return maiorIdadeSubArvore(no -> esq, maiorIdade);
            }
        }
    }
    return no;
}

No *maiorIdadeArvore(Arvore* arvore) {
    if (arvore -> raiz == NULL) {
        printf("Arvore vazia\n");
        return 0;
    }
    return maiorIdadeSubArvore(arvore -> raiz, 0);
}

No* menorIdadeSubArvore(No* no, int menorIdade) {
    if (no->dir == NULL && no->esq != NULL) {
        if (menorIdadeSubArvore(no -> esq, menorIdade)->idade < menorIdade) {
            return menorIdadeSubArvore(no -> esq, menorIdade);
        }
    }
    if (no->esq == NULL && no->dir != NULL) {
        if (menorIdadeSubArvore(no -> dir, menorIdade)->idade < menorIdade) {
            return menorIdadeSubArvore(no -> dir, menorIdade);
        }
    }
    if (no->esq != NULL && no->dir != NULL) {
        if (menorIdadeSubArvore(no -> dir, menorIdade)->idade < menorIdade) {
            if (menorIdadeSubArvore(no -> esq, menorIdade)->idade < menorIdade) {
                if (menorIdadeSubArvore(no -> dir, menorIdade)->idade < menorIdadeSubArvore(no -> esq, menorIdade)->idade) {
                    return menorIdadeSubArvore(no -> dir, menorIdade);
                } else {
                    return menorIdadeSubArvore(no -> esq, menorIdade);
                }
            } else {
                return menorIdadeSubArvore(no -> dir, menorIdade);
            }
        } else {
            if (menorIdadeSubArvore(no -> esq, menorIdade)->idade < menorIdade) {
                return menorIdadeSubArvore(no -> esq, menorIdade);
            }
        }
    }
    return no;
}

No* menorIdadeArvore(Arvore* arvore) {
    if (arvore -> raiz == NULL) {
        printf("Arvore vazia\n");
        return 0;
    }
    return menorIdadeSubArvore(arvore -> raiz, 99);
}

No* removeSubArvore(No* pai, int matricula) {
    if (pai == NULL) {
        printf("Matricula %d nao encontrada\n", matricula);
        return pai;
    }
    if (matricula > pai->matricula) {
        pai -> dir = removeSubArvore(pai -> dir, matricula);
    } else if (matricula < pai->matricula) {
        pai -> esq = removeSubArvore(pai -> esq, matricula);
    } else {
        //ACHOU O NO

        if (pai->dir == NULL && pai->esq == NULL) {
            free(pai);
            pai = NULL;
        } else if (pai->esq == NULL && pai->dir != NULL) {
            No* aux = pai;
            pai = pai -> dir;
            free(aux);
        } else if (pai->dir == NULL && pai->esq != NULL) {
            No* aux = pai;
            pai = pai -> esq;
            free(aux);
        } else if (pai->dir != NULL && pai->esq != NULL) {
            No* aux = pai -> esq;
            while (aux->dir != NULL) aux = aux -> dir;
            pai -> matricula = aux -> matricula;
            aux -> matricula = matricula;
            pai -> esq = removeSubArvore(pai -> esq, matricula);
        }
    }
    return pai;
}

int removeArvore(Arvore* arvore, int matricula) {
    if (arvore->raiz == NULL) {
        printf("\n\tArvore vazia");
        return 0;
    }
    if (arvore->raiz->matricula == matricula && arvore->raiz->dir == NULL && arvore->raiz->esq == NULL) {
        free(arvore -> raiz);
        arvore -> raiz = NULL;
    } else {
        arvore -> raiz = removeSubArvore(arvore -> raiz, matricula);
    }
    return 1;
}

No* buscaSubArvore(No* no, int matricula) {
    if (no == NULL) {
        //printf("No %d nao encontrado na arvore\n", matricula);
        return NULL;
    }
    if (matricula > no->matricula) {
        return buscaSubArvore(no -> dir, matricula);
    } else if (matricula < no->matricula) {
        return buscaSubArvore(no -> esq, matricula);
    } else {
        return no;
    }
}

No* buscaArvore(Arvore* arvore, int matricula) {
    if (arvore->raiz == NULL) {
        printf("\n\t\tArvore vazia\n");
        return NULL;
    }
    No* no = buscaSubArvore(arvore -> raiz, matricula);
    if (no != NULL) {
        return no;
    }
    return NULL;
}

bool existeNaArvore(Arvore* arvore, int matricula) {
    if (arvore->raiz == NULL) {
        printf("\n\t\tArvore vazia\n");
        return false;
    }
    No* no = buscaArvore(arvore, matricula);
    if (no != NULL) {
        return true;
    }
    return false;
}
void liberaSubArvore(No* no) {
    if (no->esq != NULL) liberaSubArvore(no -> esq);
    if (no->dir != NULL) liberaSubArvore(no -> dir);
    free(no);
}

void liberaArvore(Arvore* arvore) {
    if (arvore -> raiz != NULL) liberaSubArvore(arvore -> raiz);
    free(arvore);
}

void imprimeSubCargo(No* no, char cargo [26]){
    if (no->dir != NULL) imprimeSubCargo(no -> dir, cargo);
    if (strcmp(no -> cargo, cargo) == 0) imprimeNo(no);
    if (no->esq != NULL) imprimeSubCargo(no -> esq, cargo);
}


void imprimeCargo(Arvore* arvore, char cargo [25]){
    if (arvore -> raiz == NULL) {
        printf("Arvore vazia\n");
        return;
    }
    imprimeSubCargo(arvore ->raiz, cargo);
}

int contarNos(No* no) {
    if (no == NULL) return 0;
    return 1 + contarNos(no->esq) + contarNos(no->dir);
}

void salvarArvore(No* no, FILE* arquivo) {
    if (no == NULL) return;


    salvarArvore(no->esq, arquivo);

    char salarioString[16];
    snprintf(salarioString, sizeof(salarioString), "%.2f", no->salario);

    for (int i = 0; salarioString[i] != '\0'; i++) {
        if (salarioString[i] == '.') {
            salarioString[i] = ',';
            break;
        }
    }

    fprintf(arquivo, "%-4d %-40s %-2d %-25s %15s\n",
            no->matricula,
            no->nome,
            no->idade,
            no->cargo,
            salarioString);


    salvarArvore(no->dir, arquivo);
}


#endif
