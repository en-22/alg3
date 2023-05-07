#include <stdlib.h>
#include <stdio.h>
#include "AVLTree.h"

int main(){
	struct no *n = NULL;
	char opcao;
	int chave;
	while (!feof(stdin)){
		scanf(" %c %d", &opcao, &chave);
		switch (opcao){
			case 'i':
				n = inclui (n, chave);
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
