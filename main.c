#include <stdlib.h>
#include <stdio.h>

struct no{
	int chave;
	int altura;
	struct no *esq, *dir, *pai;
};

struct no *cria_no(int chave){
	struct no *n;
	if(!(n = malloc(sizeof(struct no))))
		return NULL;
	n->chave = chave;
	n->altura = 0;
	n->esq = NULL;
	n->dir = NULL;
	n->pai = NULL;
	return n;
}

int altura (struct no *no){
    if (!no)
        return -1;
    return no->altura;
}

int maior (int a, int b){
    return (a > b)? a : b;
}

int nivelNo(struct no* raiz, int chave){
    int nivel = -1; 
    if (!raiz)
        return -1;
    if ((raiz->chave == chave) || (nivel = nivelNo(raiz->esq, chave)) >= 0 || (nivel = nivelNo(raiz->dir, chave)) >= 0)
        return nivel + 1;
    return nivel;
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

int fatorDeBalanceamento (struct no *no){
    if (!no)
        return 0;
    return altura(no->esq) - altura(no->dir);
}

int size(struct no *n){
	if(n == NULL)
		return 0;
	return size(n->esq)+size(n->dir)+1;
}

void emordem(struct no *n, struct no *raiz){
	if(n == NULL)
		return;
	emordem(n->esq, raiz);
	printf("%d,%d,%d\n", n->chave, nivelNo(raiz, n->chave), n->altura);
	emordem(n->dir, raiz);
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
	n->altura = maior(altura(n->esq), altura(n->dir)) + 1;
	y->altura = maior(altura(y->esq), altura(y->dir)) + 1;
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
	n->altura = maior(altura(n->esq), altura(n->dir)) + 1;
	y->altura = maior(altura(y->esq), altura(y->dir)) + 1;
	y->dir = n;
	return y;
}

struct no *rot_esq_dir(struct no *n){
    n->esq = rot_esq(n->esq);
    return rot_dir(n);
}

struct no *rot_dir_esq(struct no *n){
    n->dir = rot_dir(n->dir);
    return rot_esq(n);
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

struct no *balanceia (struct no *n){
    int fator = fatorDeBalanceamento (n);
    printf ("Tome\n");
    if (fator < -1){
        if (fatorDeBalanceamento (n->dir) <= 0)
            n = rot_esq(n);
        else
            n = rot_dir_esq(n);
    }
    else if (fator > 1){
        if (fatorDeBalanceamento (n->esq) >= 0)
            n = rot_dir(n);
        else
            n = rot_esq_dir(n);
    }
    return n;
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
			n->altura = maior(altura(n->esq), altura(n->dir)) + 1;
	        n = balanceia(n);
			return n->esq;//?
		}
		return binary(n->esq, chave);
	}
	else if(n->chave < chave){
		if(n->dir == NULL){
			n->dir = cria_no(chave);
			n->dir->pai = n;
			n->altura = maior(altura(n->esq), altura(n->dir)) + 1;
	        n = balanceia(n);
			return n->dir;//
		}
		return binary(n->dir, chave);
	}
	n->altura = maior(altura(n->esq), altura(n->dir)) + 1;
	n = balanceia(n);
	return n;
}

struct no *exclui (struct no *raiz, int chave){
    struct no *sucessor, *no, *nRaiz = raiz;
    no = busca(raiz, chave);
    if (!no || !raiz)
        return NULL;
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
    nRaiz->altura = maior(altura(nRaiz->esq), altura(nRaiz->dir)) + 1;
    nRaiz = balanceia(nRaiz);
    return nRaiz;
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
	emordem(n, n);
	printf("\n");
	//n = rot_dir(n);
	//imprime_arvore(n, 0);
	//emordem(n);
	//destroi_no(n);
	return 0;
}