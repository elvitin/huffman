#include "listaFreq.c"

typedef struct huffman
{
	struct huffman *esq;
	int freq;
	int index;
	struct huffman *dir;

} NoHuff;

typedef struct floresta
{
	//struct floresta *ant;
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


//Ordem Crescente
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

////////OK
struct huffman *criaHuff(char frase[] /*, parametro da tabela de frequencia*/)
{
	struct floresta *f = NULL;
	struct tabela_frequencia *l = listaFreq(frase); //substituir por parametro

	//NoHuff *criaNoHuff(NoHuff *esq, int freq, int index, NoHuff *dir)
	//void insereFloresta(struct floresta **f, NoHuff *novoNoHuff)
	for (Tupla *auxTupla = l; auxTupla != NULL; auxTupla = auxTupla->prox)
		insereFloresta(&f, criaNoHuff(NULL, auxTupla->freq, getIndex(l, auxTupla->palavra), NULL));

	NoHuff *esq;
	NoHuff *dir;

	while (f->prox != NULL)
	{
		esq = removeFloresta(&f);
		dir = removeFloresta(&f);
		insereFloresta(&f, criaNoHuff(esq, esq->freq + dir->freq, -1, dir));
	}
	return f->arv;
}

void geraCodigo()
{
	
}

//Funcao que cria prefixos das palavras e atribui ao campo prefixo[] da tabela de frequencia  l passado por parametro
void insereCodigo(struct huffman *raiz, struct tabela_frequencia *l, int t, char cod[], int index, Tupla *auxTupla)
{
	if (raiz != NULL)
	{
		if (raiz->esq == NULL && raiz->dir == NULL)
		{
			index = getIndex(l, l->palavra);
			auxTupla = getFromIndex(l, index);
			strcpy(auxTupla->prefixo, cod);
			sprintf(auxTupla->prefixo, "%.*s", t + 1, d);
		}
		else
		{
			//verificar ordem dos bits
			t++;
			cod[t] = '1';	insereCodigos(raiz->esq, l, t, cod, index, auxTupla);
			cod[t] = '0'; 	insereCodigos(raiz->dir, l, t, cod, index, auxTupla);
			t--;
		}
	}
}

/*
void comprimir(char *frase, no *arv)
{
	char *tabela[256];
	int tam = 0;
	freq *l = listaFreq(frase);
	insereCodigos(arv, tabela, &tam, l);
	printf("\nTabela de Huffman:\n");
	for (int i = 0; i < tam; i++)
	{
		printf("%s: %s\n", tabela[i], getFromIndex(listaFreq(frase), i)->palavra);
	}
}
*/
