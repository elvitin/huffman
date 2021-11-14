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
      if (s[c] >= 'A' && s[c] <= 'Z') {
         s[c] = s[c] + 32;
      }
      c++;
   }
}

int main(void)
{
	FILE *key = fopen("chave_decodificacao.bin", "wb");
	if (key != NULL)
	{
		FILE *arq_cod = fopen("arquivo_codificado.txt", "w");
		if (arq_cod != NULL)
		{
			char frase[] = {"Amo como ama o amor. Nao conheco nenhuma outra razao para amar senao amar. Que queres que te diga, alem de que te amo, se o que quero dizer-te e que te amo?"};
			char codigo_binario[400] = "";
			char simbolos[] = ".,?";
			char frase_backup[strlen(frase)];
			lower_string(frase);
			replace(frase, simbolos);
			strcpy(frase_backup, frase);

			Tupla *auxTupla = NULL;

			struct tabela_frequencia *tabela = NULL;
			struct huffman *Arvh = criaHuff(frase, &tabela);

			printf("Exibe tabela de frequencia (Sem prefixos) ? <S/N>: ");
			if(toupper(getche()) == 'S')
			{
				putchar('\n');
				exibeTabela(tabela);
			}
			putchar('\n');
				

			//Gera prefixos e atualiza a tabela
			geraCodigo(Arvh, tabela);

			printf("Exibe tabela de frequencia (Com prefixos) ? <S/N>: ");
			
			if(toupper(getche()) == 'S')
			{
				putchar('\n');
				exibeTabela(tabela);
			}				
			putchar('\n');	

			
			char *palavra = strtok(frase_backup, " ");
			while (palavra != NULL)
			{
				auxTupla = getFromPalavra(tabela, palavra);
				if(auxTupla != NULL)
					strcat(codigo_binario, auxTupla->prefixo);
				
				palavra = strtok(NULL, " ");
			}

			fputs(codigo_binario, arq_cod);

			for(auxTupla = tabela; auxTupla != NULL; auxTupla = auxTupla->prox)
				fwrite(auxTupla, sizeof(Tupla), 1, key);

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

	return 0;
}
