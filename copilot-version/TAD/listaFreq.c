typedef struct tabela_frequencia
{
	char palavra[50];
	int freq;
	char prefixo[30];
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


////////OK
struct tabela_frequencia *listaFreq(char frase[])
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
			while (aux != NULL && strcmp(p, aux->palavra))
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
	while (auxTupla != NULL && strcmp(p, auxTupla->palavra))
	{
		auxTupla = auxTupla->prox;
		i++;
	}

	if (auxTupla == NULL)
		return -1;
	return i;
}

/*
int getFreq(freq *lista, char *p)
{
	freq *aux = lista;
	while (aux != NULL && strcmp(p, aux->palavra))
		aux = aux->prox;
	if (aux == NULL)
		return 0;
	else
		return aux->freq;
}
*/


/*
freq *getFromIndex(freq *lista, int i)
{
	freq *aux = lista;
	while (aux != NULL && i > 0)
	{
		aux = aux->prox;
		i--;
	}
	if (aux == NULL)
		return NULL;
	else
		return aux;
}
*/