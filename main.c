#include <stdlib.h>
#include <stdio.h>
/******************************************Criação do nó********************************************/
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

void destroi_no(struct no *n){
	return;
}
/******************************************Auxiliares********************************************/
int maior (int a, int b){
    return (a > b)? a : b;
}

int altura(struct no *no){
    if (!no)
        return -1;
    return no->altura;
}

int nivelNo(struct no* raiz, int chave){
    int nivel = -1; 
    if (!raiz)
        return -1;
    if ((raiz->chave == chave) || (nivel = nivelNo(raiz->esq, chave)) >= 0 || (nivel = nivelNo(raiz->dir, chave)) >= 0)
        return nivel + 1;
    return nivel;
}

int fatorDeBalanceamento (struct no *no){
    if (!no)
        return 0;
    return (altura(no->dir) - altura(no->esq));
}

int size(struct no *n){
	if(n == NULL)
		return 0;
	return size(n->esq)+size(n->dir)+1;
}

struct no *rot_esq(struct no *n){
	struct no *y = n->dir;
	n->dir = y->esq;
	y->pai = n->pai;
	n->pai = y;

	if(y->esq != NULL)
		y->esq->pai = n;
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
    y->dir = n;
    
	n->altura = maior(altura(n->esq), altura(n->dir)) + 1;
	y->altura = maior(altura(y->esq), altura(y->dir)) + 1;

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

struct no *max (struct no *no){
    if (!no->dir)
        return no;
    return max(no->dir);
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
/******************************************Balanceamento********************************************/
struct no *balanceia (struct no *n){
    int fator = fatorDeBalanceamento (n);

    if (fator < -1){
        if (fatorDeBalanceamento (n->esq) >= 0){
            n->esq = rot_esq(n->esq);
            n = rot_dir(n);
        }
        else
           n = rot_dir(n);
    }        
    else if (fator > 1){
        if (fatorDeBalanceamento (n->dir) <= 0){
                n->dir = rot_dir(n->dir);
                n = rot_esq(n);
        }
        else
            n = rot_esq(n);
    }
    return n;
}
/******************************************Inclusao********************************************/
struct no *inclui_folha(struct no *n, int chave){
	if(n == NULL){
		n = cria_no(chave);
		return n;
	}
	if(n->chave > chave){
			n->esq = inclui_folha (n->esq, chave);
			n->esq->pai = n;
	}
	else if(n->chave < chave){
		    n->dir = inclui_folha (n->dir, chave);
			n->dir->pai = n;
	}
	n->altura = maior(altura(n->esq), altura(n->dir)) + 1;
	n = balanceia(n);
	return n;
}

/******************************************Exclusao********************************************/
struct no *exclui (struct no *raiz, int chave){
    struct no *ant, *no, *nRaiz = raiz;
    no = busca(raiz, chave);
    if (!no || !raiz)
        return NULL;
    if (!no->esq)
        ajustaPai(no, no->dir);
    else{
        if (!no->dir)
            ajustaPai (no, no->esq);
        else{
            ant = max(no->esq);
            ajustaPai(ant, ant->esq);
            ant->esq = no->esq;
            ant->dir = no->dir;
            ajustaPai (no, ant);
            if (no == raiz)
                nRaiz = ant;
        }
    }
    free (no);
    nRaiz->altura = maior(altura(nRaiz->esq), altura(nRaiz->dir)) + 1;
    nRaiz = balanceia(nRaiz);
    return nRaiz;
}

/******************************************Impressao********************************************/
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

void emordem(struct no *n, struct no *raiz){
	if(n == NULL)
		return;
	emordem(n->esq, raiz);
	printf("%d,%d, %d\n", n->chave, nivelNo(raiz, n->chave), altura(n));
	emordem(n->dir, raiz);
}
/******************************************Main********************************************/
int main(){
	struct no *n = NULL;
	char opcao;
	int chave;
	/*while (!feof(stdin)){
		scanf("%c %d", &opcao, &chave);
		switch (opcao){
			case 'i':
				n = inclui_folha (n, chave);
			break;
			case 'r':
				n = exclui (n, chave);
			break;
		}
	}*/
	n = inclui_folha (n, 10);
	n = inclui_folha (n, 20);
	n = inclui_folha (n, 30);
	n = inclui_folha (n, 40);
	n = inclui_folha (n, 50);
	n = inclui_folha (n, 45);
	n = inclui_folha (n, 48);
	n = exclui (n, 40);
	n = inclui_folha (n, 5);
	n = inclui_folha (n, 4);
	n = inclui_folha (n, 3);
	n = exclui (n, 50);
	n = exclui (n, 45);
	imprime_arvore(n,0);
	emordem (n, n);
	return 0;
}
