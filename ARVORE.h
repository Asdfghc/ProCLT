#ifndef ARVORE_H_INCLUDED
#define ARVORE_H_INCLUDED

/* FUNCOES DE MANIPULACAO DE ARVORE 

*/

typedef struct No {
    int matricula, idade;
    char nome[41], cargo[26];
    float salario;
    int altura;
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

void imprimeNo(No* no) {
    printf("Matrícula: %d\nNome:%s\nIdade: %d\nCargo:%s\nSalário: %.2f\n\n", no -> matricula, no -> nome, no -> idade, no -> cargo, no -> salario);
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
        printf("Árvore vazia\n");
        return;
    }
    printf("\n");
    imprimeSubArvore(arvore -> raiz, tipo);
    printf("\n");
}

int altura(No *no) {
    return no ? no->altura : 0;
}

void atualizaAltura(No *no) {
    if (no) {
        int alturaEsq = altura(no->esq);
        int alturaDir = altura(no->dir);
        no->altura = 1 + (alturaEsq > alturaDir ? alturaEsq : alturaDir);
    }
}

int fatorBalanceamento(No *no) {
    return no ? altura(no->esq) - altura(no->dir) : 0;
}

No* rotacaoDireita(No* y) {
    No *x = y->esq;
    No *T2 = x->dir;

    x->dir = y;
    y->esq = T2;

    atualizaAltura(y);
    atualizaAltura(x);

    return x;
}

No* rotacaoEsquerda(No* x) {
    No* y = x->dir;
    No* T2 = y->esq;

    y->esq = x;
    x->dir = T2;

    atualizaAltura(x);
    atualizaAltura(y);

    return y;
}

No *balancear(No *no) {
    int fb = fatorBalanceamento(no);

    if (fb > 1 && fatorBalanceamento(no->esq) >= 0)
        return rotacaoDireita(no);

    if (fb > 1 && fatorBalanceamento(no->esq) < 0) {
        no->esq = rotacaoEsquerda(no->esq);
        return rotacaoDireita(no);
    }

    if (fb < -1 && fatorBalanceamento(no->dir) <= 0)
        return rotacaoEsquerda(no);

    if (fb < -1 && fatorBalanceamento(no->dir) > 0) {
        no->dir = rotacaoDireita(no->dir);
        return rotacaoEsquerda(no);
    }

    return no;
}

No* inserirAVL(No* no, int matricula, char nome[], int idade, char cargo[], float salario) {
    if (no == NULL) {
        No *novo = (No *)malloc(sizeof(No));
        novo->matricula = matricula;
        strcpy(novo->nome, nome);
        novo->idade = idade;
        strcpy(novo->cargo, cargo);
        novo->salario = salario;
        novo->esq = novo->dir = NULL;
        novo->altura = 1;
        return novo;
    }

    if (matricula < no->matricula)  no->esq = inserirAVL(no->esq, matricula, nome, idade, cargo, salario);
    else if (matricula > no->matricula) no->dir = inserirAVL(no->dir, matricula, nome, idade, cargo, salario);
    else{
        return no;
    }
    atualizaAltura(no);

    return balancear(no);
}

No *removerAVL(No *no, int matricula) {
    if (no == NULL)
        return no;

    if (matricula < no->matricula)
        no->esq = removerAVL(no->esq, matricula);
    else if (matricula > no->matricula)
        no->dir = removerAVL(no->dir, matricula);
    else {
        if (no->esq == NULL || no->dir == NULL) {
            No *temp = no->esq ? no->esq : no->dir;
            free(no);
            return temp;
        } else {
            No *temp = no->esq;
            while (temp->dir != NULL)
                temp = temp->dir;
            no->matricula = temp->matricula;
            strcpy(no->nome, temp->nome);
            no->idade = temp->idade;
            strcpy(no->cargo, temp->cargo);
            no->salario = temp->salario;
            no->esq = removerAVL(no->esq, temp->matricula);
        }
    }

    atualizaAltura(no);

    return balancear(no);
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

int maiorIdadeArvore(Arvore* arvore) {
    if (arvore -> raiz == NULL) {
        printf("Árvore vazia\n");
        return 0;
    }
    return maiorIdadeSubArvore(arvore -> raiz, 0) -> idade;
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

int menorIdadeArvore(Arvore* arvore) {
    if (arvore -> raiz == NULL) {
        printf("Árvore vazia\n");
        return 0;
    }
    return menorIdadeSubArvore(arvore -> raiz, 99) -> idade;
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
        printf("\n\t\tÁrvore vazia\n");
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
        printf("\n\t\tÁrvore vazia\n");
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
        printf("Árvore vazia\n");
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

bool estaBalanceada(No *no) {
    if (no == NULL) {
        return true; 
    }

    int alturaEsq = altura(no->esq);
    int alturaDir = altura(no->dir);
    int fator = alturaEsq - alturaDir;

    if (abs(fator) > 1) {
        return false;
    }

    return estaBalanceada(no->esq) && estaBalanceada(no->dir);
}



#endif 
