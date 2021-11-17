#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "src/huffman.c"

#ifdef __linux__
	#include "src/getchForLinux.h"
#else
	#include <conio.h>
#endif


void exibe(struct tabela_frequencia *tabela)
{
	if(*tabela->prefixo != '\0')
		printf("Exibe tabela de frequencia (Com prefixos) ? <S/N>: ");
	else
		printf("Exibe tabela de frequencia (Sem prefixos) ? <S/N>: ");

	if (toupper(getche()) == 'S')
	{
		putchar('\n');
		exibeTabela(tabela);
	}
	putchar('\n');
}

void decodificar(struct huffman *A, struct tabela_frequencia *tabela, FILE *arq_cod)
{
	char c;
	char frase[3500] = "";
	NoHuff *auxNoHuff = A;
	Tupla *auxTupla;

	if (A != NULL)
	{
		c = fgetc(arq_cod);
		while (!feof(arq_cod))
		{
			auxNoHuff = c == '0' ? auxNoHuff->esq : auxNoHuff->dir;

			if (auxNoHuff->esq == NULL && auxNoHuff->dir == NULL)
			{
				auxTupla = getFromIndex(tabela, auxNoHuff->index);
				strcat(frase, auxTupla->palavra);
				strcat(frase, " ");
				auxNoHuff = A;
			}

			c = fgetc(arq_cod);
		}
	}
	puts(frase);
}

struct tabela_frequencia *carregaTabela(FILE *key)
{
	struct tabela_frequencia *tabela;

	Tupla auxRegTupla;
	Tupla *auxPonteiroTupla;
	Tupla *ultimo;

	fread(&auxRegTupla, sizeof(Tupla), 1, key);

	while (!feof(key))
	{
		auxPonteiroTupla = malloc(sizeof(Tupla));

		strcpy(auxPonteiroTupla->palavra, auxRegTupla.palavra);
		auxPonteiroTupla->freq = auxRegTupla.freq;
		strcpy(auxPonteiroTupla->prefixo, auxRegTupla.prefixo);
		auxPonteiroTupla->prox = NULL;

		if (tabela == NULL)
		{
			tabela = auxPonteiroTupla;
			ultimo = auxPonteiroTupla;
		}
		else
		{
			ultimo->prox = auxPonteiroTupla;
			ultimo = ultimo->prox;
		}

		fread(&auxRegTupla, sizeof(Tupla), 1, key);
	}

	return tabela;
}

int main(void)
{
	FILE *key = fopen("arquivos_gerados/chave_decodificacao.bin", "rb");
	if (key != NULL)
	{
		FILE *arq_cod = fopen("arquivos_gerados/arquivo_codificado.txt", "r");
		if (arq_cod != NULL)
		{
			struct huffman *Arvh;
			struct tabela_frequencia *tabela;

			tabela = carregaTabela(key);
			exibe(tabela);

			Arvh = criaHuffTabela(tabela);
			decodificar(Arvh, tabela, arq_cod);

			destroiHuffman(&Arvh);
			destroiTabela(&tabela);

			fclose(arq_cod);
		}
		else
			perror("Erro (ArqTxt)");

		fclose(key);
	}
	else
		perror("Erro (ArqBin)");

	getch();
	return 0;
}
