#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct NoTrie {
  struct NoTrie *filhos[26];
  int fimDaPalavra;
} NoTrie;

NoTrie *criarNo() {
  NoTrie *no = (NoTrie *)malloc(sizeof(NoTrie));
  if (no) {
    no->fimDaPalavra = 0;
    for (int i = 0; i < 26; i++) {
      no->filhos[i] = NULL;
    }
  }
  return no;
}

void inserirPalavra(NoTrie *raiz, char *palavra) {
  NoTrie *no = raiz;
  int comprimento = strlen(palavra);

  for (int i = 0; i < comprimento; i++) {
    int indice = palavra[i] - 'a';
    if (!no->filhos[indice]) {
      no->filhos[indice] = criarNo();
    }
    no = no->filhos[indice];
  }

  no->fimDaPalavra = 1;
}

int buscarPalavra(NoTrie *raiz, char *palavra) {
  NoTrie *no = raiz;
  int comprimento = strlen(palavra);

  for (int i = 0; i < comprimento; i++) {
    int indice = palavra[i] - 'a';
    if (!no->filhos[indice]) {
      return 0;
    }
    no = no->filhos[indice];
  }

  return (no != NULL && no->fimDaPalavra) ? 1 : 0;
}

int noVazio(NoTrie *no) {
  for (int i = 0; i < 26; i++) {
    if (no->filhos[i] != NULL) {
      return 0;
    }
  }
  return 1;
}

NoTrie *removerPalavra(NoTrie *raiz, char *palavra, int profundidade) {
  if (!raiz) {
    return NULL;
  }

  if (profundidade == strlen(palavra)) {
    if (raiz->fimDaPalavra) {
      raiz->fimDaPalavra = 0;
    }

    if (noVazio(raiz) && !raiz->fimDaPalavra) {
      free(raiz);
      raiz = NULL;
    }

    return raiz;
  }

  int indice = palavra[profundidade] - 'a';
  raiz->filhos[indice] = removerPalavra(raiz->filhos[indice], palavra, profundidade + 1);

  if (noVazio(raiz) && !raiz->fimDaPalavra) {
    free(raiz);
    raiz = NULL;
  }

  return raiz;
}

int contarPalavras(NoTrie *raiz) {
  if (!raiz) {
    return 0;
  }

  int count = 0;

  if (raiz->fimDaPalavra) {
    count++;
  }

  for (int i = 0; i < 26; i++) {
    count += contarPalavras(raiz->filhos[i]);
  }

  return count;
}

void liberarTrie(NoTrie *raiz) {
  if (!raiz) {
    return;
  }

  for (int i = 0; i < 26; i++) {
    liberarTrie(raiz->filhos[i]);
  }

  free(raiz);
}

int main() {
  NoTrie *raiz = criarNo();

  inserirPalavra(raiz, "cachorro");
  inserirPalavra(raiz, "casa");
  inserirPalavra(raiz, "cadeira");

  printf("Número total de palavras na Trie: %d\n", contarPalavras(raiz));

  if (buscarPalavra(raiz, "casa") == 1) {
    printf("A palavra 'casa' está presente na Trie.\n");
  } else {
    printf("A palavra 'casa' não está presente na Trie.\n");
  }

  raiz = removerPalavra(raiz, "casa", 0);

  if (buscarPalavra(raiz, "casa") == 1) {
    printf("A palavra 'casa' está presente na Trie.\n");
  } else {
    printf("A palavra 'casa' não está presente na Trie.\n");
  }

  printf("Número total de palavras na Trie após remoção: %d\n", contarPalavras(raiz));

  liberarTrie(raiz);

  return 0;
}
