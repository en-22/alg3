#include <stdlib.h>
#include <stdio.h>

struct no{
	int chave;
	struct no *esq, *dir, *pai;
};

struct no *cria_no(int chave){
	struct no *n;
	if(!(n = malloc(sizeof(struct no))))
		return NULL;
	n->chave = chave;
	n->esq = NULL;
	n->dir = NULL;
	n->pai = NULL;
	return n;
}

void destroi_no(struct no *n){
    return;
}

void imprime_arvore(struct no *n, int esp){
	if(n == NULL)
		return;
	esp = esp + 10;
	
	imprime_arvore(n->dir, esp);
	
	printf("\n");
    for(int i = 10; i < esp; i++)
		printf(".");
    printf("%d\n", n->chave);
	
	imprime_arvore(n->esq, esp);
}

int altura_no(struct no *n){
    int alt_esq, alt_dir;
    if(n == NULL) 
        return -1;
    alt_esq = altura_no(n->esq);
    alt_dir = altura_no(n->dir);
    if (alt_esq > alt_dir)
        return alt_esq + 1;
    return alt_dir + 1; 
}

int nivel_no(struct no* raiz, int chave){
    int nivel = -1; 
    if (!raiz)
        return -1;
    if ((raiz->chave == chave) || (nivel = nivel_no(raiz->esq, chave)) >= 0 || (nivel = nivel_no(raiz->dir, chave)) >= 0)
        return nivel + 1;
    return nivel;
}

int size(struct no *n){
	if(n == NULL)
		return 0;
	return size(n->esq)+size(n->dir)+1;
}

struct no *busca(struct no *n, int chave){
	if(!n)
		return NULL;
	if(chave == n->chave)
		return n;
	if(chave < n->chave)
		return busca(n->esq, chave);
	return busca(n->dir, chave);
}

struct no *rot_esq(struct no *n){
	struct no *y = n->dir;
    n->dir = y->esq;
	y->pai = n->pai;
	n->pai = y;

	if(y->esq != NULL)
		y->esq->pai = n;
	y->esq = n;
	return y;
}

struct no *rot_dir(struct no *n){
	struct no *y = n->esq;
	n->esq = y->dir;
	y->pai = n->pai;
	n->pai = y;

	if(y->dir != NULL)
		y->dir->pai = n;
	
	y->dir = n;
	return y;
}

struct no *inclui_folha(struct no *n, int chave){
	if(n == NULL){
		n = cria_no(chave);
		return n;
	}
	if(n->chave > chave){
		if(n->esq == NULL){
			n->esq = cria_no(chave);
			n->esq->pai = n;
			return n->esq;
		}
		return inclui_folha(n->esq, chave);
	}
	else if(n->chave < chave){
		if(n->dir == NULL){
			n->dir = cria_no(chave);
			n->dir->pai = n;
			return n->dir;
			}
		return inclui_folha(n->dir, chave);
	}
	return n;
}
struct no* inclui_raiz(struct no *n, int chave){
    if(n == NULL){
		n = cria_no(chave);
		return n;
	}
   if(chave < n->chave){
	    n->esq = inclui_raiz(n->esq, chave);
	    n->esq->pai = n;
	    n = rot_dir(n);
	    return n;
    }       
	else{//(chave > n->chave)
	    n->dir = inclui_raiz(n->dir, chave);
	    n->dir->pai = n;
        n = rot_esq(n);
	    return n;
	}
}

struct no *min (struct no *no){
    if (!no->esq)
        return no;
    return min(no->esq);
}

void ajustaPai (struct no *no, struct no *novo){
    if (no->pai){
        if (no->pai->esq == no)
            no->pai->esq = novo;
        else
            no->pai->dir = novo;
        if (novo)
            novo->pai = no->pai;
    }
}

struct no *exclui (struct no *raiz, int chave){
    struct no *sucessor, *no, *nRaiz = raiz;
    no = busca(raiz, chave);
    if (!no->esq)
        ajustaPai(no, no->dir);
    else{
        if (!no->dir)
            ajustaPai (no, no->esq);
        else{
            sucessor = min(no->dir);
            ajustaPai(sucessor, sucessor->dir);
            sucessor->esq = no->esq;
            sucessor->dir = no->dir;
            ajustaPai (no, sucessor);
            if (no == raiz)
                nRaiz = sucessor;
        }
    }
    free (no);
    return nRaiz;
}


void emordem(struct no *n, struct no *raiz){
	if(n == NULL)
		return;
	emordem(n->esq, raiz);
	printf("%d,%d\n", n->chave, nivel_no(raiz, n->chave));
	emordem(n->dir, raiz);
}

int main(){
	struct no *n = inclui_folha(n, 8);
	inclui_folha(n, 3);
	inclui_folha(n, 10);
	inclui_folha(n, 1);
	inclui_folha(n, 9);
	inclui_folha(n, 14);
	imprime_arvore(n, 0);
	emordem(n, n);
	printf("\n");
	inclui_raiz(n, 6);
	imprime_arvore(n, 0);
	emordem(n, n);
	return 0
}
