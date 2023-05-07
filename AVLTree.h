struct no{
	int chave;
	int altura;
	struct no *esq, *dir, *pai;
};
//Cria um nó da árvore com a chave dada, altura = 0, e com os ponteiros para esq, dir e pai iguais a NULL.
struct no *cria_no (int chave);
//Libera a memória alocada pelos nós da árvore.
void destroiArvore(struct no *n);
//Retorna o nível no qual está o no da chave dada.
int nivelNo (struct no* raiz, int chave);
//Retorna a altura do nó dado a partir de seu valor na struct no.
int altura (struct no *no);
//Inclui um novo nó com a chave dada, respeitando as regras da árvore AVL, podendo rebalancear a árvore se necessário.
struct no *inclui (struct no *n, int chave);
//Exclui um nó a partir da chave dada, respeitando as regras da árvore AVL, podendo rebalancear a árvore se necessário.
struct no *exclui (struct no *n, int chave);
//Imprime os nós no formato da árvore. Para depuração.
void imprime_arvore (struct no *n, int esp);
//Imprime as chaves dos nós em ordem crescente e seus níveis, no formato "chave, nível\n".
void emordem (struct no *n, struct no *raiz);
