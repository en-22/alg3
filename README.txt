### Equipe
- Eloisa Nielsen - GRR20221226
- Tiago Mendes Bottamedi - GRR20220068

### Objetivo

O objetivo do trabalho é implementar uma árvore do tipo AVL (Adelson-Velsky Landis) com operações de inserção e remoção, baseado nos algoritmos vistos em sala. 

### Implementação

- A árvore foi implementada com uma estrutura de nó que contém uma chave (int), ponteiros para o pai e para os filhos esquerdo e direito, e sua altura, conforme a ilustração abaixo:

struct no{
	int chave;
	int altura;
	struct no *esq, *dir, *pai;
};

- Ambos os algoritmos de inclusão e exclusão possuem a mesma recursão que a busca binária de árvores para encontrar qual chave deve incluir ou excluir: caso a chave desejada seja maior que a chave do nó, a função é chamada recursivamente para o filho da direita, caso seja menor, é chamada para o filho da esquerda, até chegar no local desejado.

- Na exclusão, em especial, caso a chave seja encontrada, são testados os 3 casos possíveis: nó sem filhos, nó com 1 filho e nó com 2 filhos. No primeiro caso, o nó é removido e a função retorna NULL. No segundo caso, o nó é removido e substituído pelo seu filho. No último caso, a remoção é feita pelo antecessor, de tal forma que o nó a ser removido e seu antecessor trocam de chaves, e a função é então chamada recursivamente para o filho da esquerda. Dessa forma, a chave que se deseja remover é "empurrada" para baixo da árvore até chegar em um dos primeiros casos, facilitando a remoção.

- O balanceamento da árvore é feito no final das funções de inclusão e exclusão. A cada chamada recursiva dessas funções, é recalculada a altura do nó passado como argumento e chamada a seguinte função para balanceá-lo, onde o fator de balanceamento nada mais é que a altura da subárvore da direita menos a altura da esquerda, e caso esse fator seja diferente de -1, 0 ou 1, a árvore precisará ser rebalanceada. Os algoritmos de rotação são os mesmos vistos em aula, com a adição do cálculo da altura dos nós rotacionados. A partir do fator, escolhe-se a partir de qual lado será feita a rotação da árvore, e a partir do fator do filho, sendo ele esquerdo ou direito, ele fará uma rotação se a subárvore estiver "profundamente balanceada" e duas se a subárvore estiver em "zigzag".

struct no *balanceia (struct no *n){
    int fator = fatorDeBalanceamento(n);
    if (fator < -1){
        if (fatorDeBalanceamento(n->esq) > 0){
            n->esq = rot_esq(n->esq);
            n = rot_dir(n);
        }
        else
           n = rot_dir(n);
    }        
    else if (fator > 1){
        if (fatorDeBalanceamento(n->dir) < 0){
                n->dir = rot_dir(n->dir);
                n = rot_esq(n);
        }
        else
            n = rot_esq(n);
    }
    return n;
}

- A função "imprime_arvore" imprime os nodos deixando claro quais são os pais e os filhos de cada nodo no formato de uma árvore. A função foi utilizada para ajudar a visualizar a árvore e entender como balanceá-la.

- A função "emordem" imprime as chaves dos nodos em ordem crescente por meio de recursão, junto aos seus níveis.

- Há também funções secundárias que lidam com a alocação e desalocação de memória. Ao final do programa, toda a memória alocada é liberada.

- Por fim, o programa principal lê um caractere representando a instrução (i para inserção e r para remoção) e uma chave até o fim do "arquivo" (que no caso, é o stdin), e a cada leitura, testa qual a opção desejada e executa a operação correspondente. Caso um caractere inválido seja passado como argumento, o usuário é avisado no stderr e o programa sai com código 1.
