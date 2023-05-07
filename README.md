### Equipe
- Eloisa Nielsen - GRR20221226
- Tiago Mendes Bottamedi - GRR20220068

### Objetivo

O objetivo do trabalho é implementar uma árvore do tipo AVL (Adelson-Velsky Landis) com operações de inserção e remoção, baseado nos algoritmos vistos em sala. 

### Implementação

- A árvore foi implementada com uma estrutura de nó que contém uma chave (int), ponteiros para o pai e os filhos, e sua altura, conforme a ilustração abaixo:
```c
struct no{
	int chave;
	int altura;
	struct no *esq, *dir, *pai;
};
```
- Ambos os algoritmos de inclusão e exclusão possuem a mesma recursão que a busca binária de árvores: caso a chave desejada seja maior que a chave do nó, a função é chamada recursivamente para o filho da direita, caso seja menor, é chamada para o filho da esquerda. 

- Na exclusão, em especial, caso a chave seja encontrada, são testados os 3 casos possíveis: nó sem filhos, nó com 1 filho e nó com 2 filhos. No primeiro caso, o nó é removido e a função retorna NULL. No segundo caso, o nó é removido e substituído pelo seu filho. No último caso, a remoção é feita pelo antecessor, de tal forma que o nó a ser removido e seu antecessor trocam de chaves, e a função é então chamada recursivamente para o filho da esquerda. Dessa forma, a chave que se deseja remover é "empurrada" para baixo da árvore até chegar em um dos primeiros casos, facilitando a remoção.

- O balanceamento da árvore é feito dentro das funções de inclusão e exclusão. A cada chamada recursiva dessas funções, é recalculada a altura do nó passado como argumento e chamada a seguinte função para balanceá-lo, onde o fator de balanceamento nada mais é que a altura da sub-árvore da esquerda menos a altura da direita e os algoritmos de rotação são os mesmos vistos em aula, com a adição do recálculo da altura dos nós rotacionados.
```c
struct no *balanceia (struct no *n){
    int fator = fatorDeBalanceamento(n);
    if (fator < -1){
        if (fatorDeBalanceamento(n->esq) >= 0){
            n->esq = rot_esq(n->esq);
            n = rot_dir(n);
        }
        else
           n = rot_dir(n);
    }        
    else if (fator > 1){
        if (fatorDeBalanceamento(n->dir) <= 0){
                n->dir = rot_dir(n->dir);
                n = rot_esq(n);
        }
        else
            n = rot_esq(n);
    }
    return n;
}
```
