struct no{
	int chave;
	int altura;
	struct no *esq, *dir, *pai;
};

struct no *cria_no (int chave);

int nivelNo (struct no* raiz, int chave);

int maior (int a, int b);

int altura (struct no *no);

int fatorDeBalanceamento (struct no *no);

struct no *rot_esq (struct no *n);

struct no *rot_dir (struct no *n);

struct no *max (struct no *no);

void ajustaPai (struct no *no, struct no *novo);

struct no *balanceia (struct no *n);

struct no *inclui_folha (struct no *n, int chave);

struct no *exclui (struct no *n, int chave);

void imprime_arvore (struct no *n, int esp);

void emordem (struct no *n, struct no *raiz);

void destroiArvore(struct no *n);
