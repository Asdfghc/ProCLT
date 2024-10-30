#ifndef ARVORE_H_INCLUDED
#define ARVORE_H_INCLUDED

/* FUNCOES DE MANIPULACAO DE ARVORE 

*/

typedef struct No {
    int info;
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

void insereArvore(Arvore* arvore, int valor) {
    No* novo = (No*) malloc(sizeof(No));
    novo -> info = valor;
    novo -> esq = NULL;
    novo -> dir = NULL;
    if (arvore->raiz == NULL) {
        arvore -> raiz = novo;
    }
    else {
        int flag = 0;
        No* pai = arvore -> raiz;
        while (flag != 1) {
            if (valor > pai->info) {
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

void imprimeSubArvore(No* no, int tipo) {
    if (tipo == 0) printf(" - %d", no -> info);
    if (no->dir != NULL) imprimeSubArvore(no -> dir, tipo);
    if (tipo == 1) printf(" - %d", no -> info);
    if (no->esq != NULL) imprimeSubArvore(no -> esq, tipo);
    if (tipo == 2) printf(" - %d", no -> info);
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

No* removeSubArvore(No* pai, int valor) {
    if (pai == NULL) {
        printf("No %d nao encontrado na arvore\n", valor);
        return pai;
    }
    if (valor > pai->info) {
        pai -> dir = removeSubArvore(pai -> dir, valor);
    } else if (valor < pai->info) {
        pai -> esq = removeSubArvore(pai -> esq, valor);
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
            pai -> info = aux -> info;
            aux -> info = valor;
            pai -> esq = removeSubArvore(pai -> esq, valor);
        }
    }
    return pai;
}

void removeArvore(Arvore* arvore, int valor) {
    if (arvore->raiz == NULL) {
        printf("Arvore vazia\n");
        return;
    }
    if (arvore->raiz->info == valor && arvore->raiz->dir == NULL && arvore->raiz->esq == NULL) {
        free(arvore -> raiz);
        arvore -> raiz = NULL;
    } else {
        arvore -> raiz = removeSubArvore(arvore -> raiz, valor);
    }
}



#endif // ARVORE_H_INCLUDED
