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


int nivelNo(struct no* raiz, int chave){
    int nivel = -1; 
    if (!raiz)
        return -1;
    if ((raiz->chave == chave) || (nivel = nivelNo(raiz->esq, chave)) >= 0 || (nivel = nivelNo(raiz->dir, chave)) >= 0)
        return nivel + 1;
    return nivel;
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


int fatorDeBalanceamento (struct no *no){
    if (!no)
        return 0;
    return (altura(no->dir) - altura(no->esq));
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


struct no *exclui (struct no *n, int chave){
	if (!n)
		return NULL;
	if (n->chave == chave){
		if (!n->esq && !n->dir){
			free (n);
			return NULL;
		}
		else if (n->esq && n->dir){
			struct no *ant = max(n->esq); //Remove pelo antecessor
			n->chave = ant->chave;
			ant->chave = chave; //Joga a chave para a folha, para tornar mais fácil a remoção
			n->esq = exclui (n->esq, chave);
			return n;
		}
		else{
			struct no *aux;
			if (!n->dir)
				aux = n->esq;
			else
				aux = n->dir;
			free (n);
			return aux;
		}
	}
	else if (n->chave > chave)
		n->esq = exclui (n->esq, chave);
	else
		n->dir = exclui (n->dir, chave);
	n->altura = maior (altura(n->esq), altura(n->dir)) + 1;
	n = balanceia(n);
	return (n);
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
	printf("%d,%d\n", n->chave, nivelNo (raiz, n->chave));
	emordem(n->dir, raiz);
}


void destroiArvore(struct no *n) {
    if(n->esq)
        destroiArvore(n->esq);
    if(n->dir)
        destroiArvore(n->dir);
    free(n);
}


/******************************************Main********************************************/
int main(){
	struct no *n = NULL;
	char opcao;
	int chave;
	while (!feof(stdin)){
		scanf(" %c %d", &opcao, &chave);
		switch (opcao){
			case 'i':
				n = inclui_folha (n, chave);
			break;
			case 'r':
				n = exclui (n, chave);
			break;
			default:
				fprintf (stderr, "Argumento inválido\n");
				exit(1);
		}
	}
	emordem (n, n);
	destroiArvore (n);
	return 0;
}
