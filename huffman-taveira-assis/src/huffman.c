#include "lista_freq.c"

typedef struct huffman
{
	struct huffman *esq;
	int freq;
	int index;
	struct huffman *dir;

} NoHuff;

typedef struct floresta
{
	NoHuff *arv;
	struct floresta *prox;
} NoF;

NoHuff *criaNoHuff(NoHuff *esq, int freq, int index, NoHuff *dir)
{
	NoHuff *novoNoHuff = malloc(sizeof(NoHuff));
	novoNoHuff->esq = esq;
	novoNoHuff->freq = freq;
	novoNoHuff->index = index;
	novoNoHuff->dir = dir;
	return novoNoHuff;
}

//Ordem Crescente remove do Inicio (Cabeca de lista)
void insereFloresta(struct floresta **f, NoHuff *novoNoHuff)
{
	NoF *novoNoF = malloc(sizeof(NoF));
	novoNoF->arv = novoNoHuff;
	novoNoF->prox = NULL;

	if (*f == NULL)
		*f = novoNoF;
	else
	{
		NoF *ant = NULL;
		NoF *atual = *f;

		while (atual != NULL && atual->arv->freq < novoNoHuff->freq)
		{
			ant = atual;
			atual = atual->prox;
		}

		if (ant == NULL)
		{
			novoNoF->prox = *f;
			*f = novoNoF;
		}
		else
		{
			ant->prox = novoNoF;
			novoNoF->prox = atual;
		}
	}
}

NoHuff *removeFloresta(struct floresta **f)
{
	if (*f != NULL)
	{
		NoF *aux = *f;
		*f = (*f)->prox;
		NoHuff *novo = aux->arv;
		free(aux);
		return novo;
	}
	return NULL;
}

//Cria arvore Huffman a gerando uma tabela
struct huffman *criaHuff(char frase[], struct tabela_frequencia **tabela)
{
	struct floresta *f = NULL;
	NoHuff *auxArv;

	*tabela = criaTabelaFreq(frase);

	for (Tupla *auxTupla = *tabela; auxTupla != NULL; auxTupla = auxTupla->prox)
		insereFloresta(&f, criaNoHuff(NULL, auxTupla->freq, getIndex(*tabela, auxTupla->palavra), NULL));

	NoHuff *esq = NULL;
	NoHuff *dir = NULL;

	while (f->prox != NULL)
	{
		esq = removeFloresta(&f);
		dir = removeFloresta(&f);
		insereFloresta(&f, criaNoHuff(esq, esq->freq + dir->freq, -1, dir));
	}

	auxArv = f->arv;
	free(f);
	return auxArv;
}

//Cria arvore Huffman a partir de uma tabela
struct huffman *criaHuffTabela(struct tabela_frequencia *tabela)
{
	struct floresta *f = NULL;
	NoHuff *auxArv;

	for (Tupla *auxTupla = tabela; auxTupla != NULL; auxTupla = auxTupla->prox)
		insereFloresta(&f, criaNoHuff(NULL, auxTupla->freq, getIndex(tabela, auxTupla->palavra), NULL));

	NoHuff *esq = NULL;
	NoHuff *dir = NULL;

	while (f->prox != NULL)
	{
		esq = removeFloresta(&f);
		dir = removeFloresta(&f);
		insereFloresta(&f, criaNoHuff(esq, esq->freq + dir->freq, -1, dir));
	}
	
	auxArv = f->arv;
	free(f);
	return auxArv;
}


//Funcao que cria prefixos das palavras e atribui ao campo prefixo[] da tabela de frequencia tabela passado por parametro
void insereCodigo(struct huffman *raiz, struct tabela_frequencia *tabela, int t, char cod[], int index, Tupla *auxTupla)
{
	if (raiz != NULL)
	{
		if (raiz->esq == NULL && raiz->dir == NULL)
		{
			auxTupla = getFromIndex(tabela, raiz->index);
			sprintf(auxTupla->prefixo, "%.*s", t + 1, cod);
		}
		else
		{
			t++;
			cod[t] = '0'; insereCodigo(raiz->esq, tabela, t, cod, index, auxTupla);
			cod[t] = '1'; insereCodigo(raiz->dir, tabela, t, cod, index, auxTupla);
			t--;
		}
	}
}

void geraCodigo(struct huffman *raiz, struct tabela_frequencia *tabela)
{
	char buffstring[50];
	insereCodigo(raiz, tabela, -1, buffstring, 0, NULL);
}

void destroiHuffman(struct huffman **raiz)
{
	if (*raiz != NULL)
	{
		destroiHuffman(&(*raiz)->esq);
		destroiHuffman(&(*raiz)->dir);
		free(*raiz);
		*raiz = NULL;
	}
}
