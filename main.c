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

/*void destroi_no(struct no *n){
	if(n == NULL)
		return;
	destroi_no(n->esq);
	free(n);
	destroi_no(n->dir);
}*/

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

struct no *binary(struct no *n, int chave){//um inclui na folha, na realidade
//	if(n == NULL){
//		n = cria_no(chave);
//		return n;
//	}
	if(n->chave > chave){
		if(n->esq == NULL){
			n->esq = cria_no(chave);
			n->esq->pai = n;
			return n->esq;//?
		}
		return binary(n->esq, chave);
	}
	else if(n->chave < chave){
		if(n->dir == NULL){
			n->dir = cria_no(chave);
			n->dir->pai = n;
			return n->dir;//
		}
		return binary(n->dir, chave);
	}
	return n;
}

int size(struct no *n){
	if(n == NULL)
		return 0;
	return size(n->esq)+size(n->dir)+1;
}

void emordem(struct no *n){
	if(n == NULL)
		return;
	emordem(n->esq);
	printf("%d ", n->chave);
	emordem(n->dir);
}

struct no *rot_esq(struct no *n){
	struct no *y = n->dir;
	n->dir = y->esq;
	y->pai = n->pai;
	n->pai = y;

	if(y->esq != NULL)
		y->esq->pai = n;

	//if(n->pai == NULL)
	//	T.raiz = y;
	//if(n == n->pai->esq)
	//	n->pai->esq = y;
	//else
	//	n->pai->dir = y;
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

	//if(n->pai == NULL)
	//	T.raiz = y;
	//if(n == n->pai->esq)
	//	n->pai->esq = y;
	//else
	//	n->pai->dir = y;
	y->dir = n;
		return y;
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

struct no* inclui_raiz(struct no *n, int chave){
	if(n == NULL){
		n = cria_no(chave);
		return n;
	}
	if(chave < n->chave){
		n->esq = inclui_raiz(n->esq, chave);
		n->esq->pai = n;
		n = rot_dir(n);
	}else{
		n->dir = inclui_raiz(n->esq, chave);
		n->dir->pai = n;
		n = rot_esq(n);
	}
	
	return n;
}

int main(){
	struct no *n = cria_no(12);
	binary(n, 5);
	binary(n, 10);
	binary(n, 11);
	binary(n, 4);
	binary(n, 2);
	binary(n, 6);
	imprime_arvore(n, 0);
	emordem(n);
	printf("\n");
	//n = rot_dir(n);
	//imprime_arvore(n, 0);
	//emordem(n);
	//destroi_no(n);
	return 0;
}
