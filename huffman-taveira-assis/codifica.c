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

void replace(char *string, char *characters)
{
	int len = strlen(string);
	int charlen = strlen(characters);
	int j;
	for (int i = 0; i < len; i++)
		for (j = 0; j < charlen; j++)
			if (characters[j] == string[i])
				string[i] = ' ';
}

void lower_string(char s[])
{
	int c = 0;

	while (s[c] != '\0')
	{
		if (s[c] >= 'A' && s[c] <= 'Z')
		{
			s[c] = s[c] + 32;
		}
		c++;
	}
}

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

//Codifica usando a tabela e gravando em arq_cod
void codificar(char *palavras, struct tabela_frequencia *tabela, FILE *arq_cod)
{
	Tupla *auxTupla;
	char codigo_binario[1000] = "";

	char *palavra = strtok(palavras, " ");
	while (palavra != NULL)
	{
		auxTupla = getFromPalavra(tabela, palavra);
		if (auxTupla != NULL)
			strcat(codigo_binario, auxTupla->prefixo);

		palavra = strtok(NULL, " ");
	}
	fputs(codigo_binario, arq_cod);
}

void gravaTabela(struct tabela_frequencia *tabela, FILE *key)
{
	for (Tupla *auxTupla = tabela; auxTupla != NULL; auxTupla = auxTupla->prox)
		fwrite(auxTupla, sizeof(Tupla), 1, key);
}

int main(void)
{
	FILE *key = fopen("arquivos_gerados/chave_decodificacao.bin", "wb");
	if (key != NULL)
	{
		FILE *arq_cod = fopen("arquivos_gerados/arquivo_codificado.txt", "w");
		if (arq_cod != NULL)
		{
			struct huffman *Arvh;
			struct tabela_frequencia *tabela;

			char frase[] = {"Amo como ama o amor. Nao conheco nenhuma outra razao para amar senao amar. Que queres que te diga, alem de que te amo, se o que quero dizer-te e que te amo?"};
			char frase_backup[strlen(frase)];
			char simbolos[] = ".,?";

			replace(frase, simbolos);
			lower_string(frase);
			strcpy(frase_backup, frase);

			Arvh = criaHuff(frase, &tabela);
			exibe(tabela);

			geraCodigo(Arvh, tabela); //Gera prefixos e atualiza a tabela
			exibe(tabela);

			codificar(frase_backup, tabela, arq_cod);

			gravaTabela(tabela, key);

			destroiTabela(&tabela);
			destroiHuffman(&Arvh);

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
