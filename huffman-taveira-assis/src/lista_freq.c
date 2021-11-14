typedef struct tabela_frequencia
{
	char palavra[50];
	int freq;
	char prefixo[50]; //Ou codigo
	struct tabela_frequencia *prox;

} Tupla;

Tupla *criaTuplaFreq(char *p)
{
	Tupla *novaTupla = malloc(sizeof(Tupla));
	strcpy(novaTupla->palavra, p);
	novaTupla->freq = 1;
	strcpy(novaTupla->prefixo, "");
	novaTupla->prox = NULL;
	return novaTupla;
}

struct tabela_frequencia *criaTabelaFreq(char frase[])
{
	char *p = strtok(frase, " ");

	Tupla *cabeca = criaTuplaFreq(p);
	Tupla *ultimo = cabeca;
	Tupla *aux;

	while (p != NULL)
	{
		p = strtok(NULL, " ");
		
		if (p != NULL)
		{
			aux = cabeca;
			while (aux != NULL && strcasecmp(p, aux->palavra))
				aux = aux->prox;

			if (aux == NULL)
			{
				ultimo->prox = criaTuplaFreq(p);
				ultimo = ultimo->prox;
			}
			else
				aux->freq++;
		}
	}
	return cabeca;
}

int getIndex(struct tabela_frequencia *lista, char p[])
{
	Tupla *auxTupla = lista;

	int i = 0;
	while (auxTupla != NULL && strcasecmp(p, auxTupla->palavra))
	{
		auxTupla = auxTupla->prox;
		i++;
	}

	if (auxTupla == NULL)
		return -1;
	return i;
}

Tupla *getFromIndex(struct tabela_frequencia *lista, int i)
{
	Tupla *auxTupla = lista;
	while (auxTupla != NULL && i > 0)
	{
		auxTupla = auxTupla->prox;
		i--;
	}

	if (auxTupla == NULL)
		return NULL;
	return auxTupla;
}

Tupla *getFromPalavra(Tupla *tabela, char p[])
{
	Tupla *auxTupla = tabela;
	while (auxTupla != NULL && strcasecmp(p, auxTupla->palavra))
		auxTupla = auxTupla->prox;

	return auxTupla;
}

void exibeTabela(struct tabela_frequencia *tabela)
{	
	puts("\n================================================");
	puts("[Palavra]\t[Frequencia]\t[Codigo/Prefixo]");
	puts("================================================");
	while (tabela != NULL)
	{
		printf(" %-16s%-16d%s\n", tabela->palavra, tabela->freq, tabela->prefixo);
		tabela = tabela->prox;
	}
	putchar('\n');
}

void destroiTabela(struct tabela_frequencia **tabela)
{
	if (*tabela != NULL)
	{
		destroiTabela(&(*tabela)->prox);
		free(*tabela);
		*tabela = NULL;
	}
}
