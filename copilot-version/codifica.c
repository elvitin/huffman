#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "src/huffman.c"


//strcasecmp()

int main(void)
{
	FILE *key = fopen("chave_decodificacao.bin", "wb");
	if (key != NULL)
	{
		FILE *arq_cod = fopen("arquivo_codificado.txt", "w");
		if (arq_cod != NULL)
		{
			char frase[] = "Amo como ama o amor. Não conheço nenhuma outra razão para amar senão amar. Que queres que te diga, além de que te amo, se o que quero dizer-te é que te amo?";
			char frase_backup[] = "Amo como ama o amor. Não conheço nenhuma outra razão para amar senão amar. Que queres que te diga, além de que te amo, se o que quero dizer-te é que te amo?";
			char codigo_binario[100] = "";
			

			Tupla *auxTupla = NULL;

			struct tabela_frequencia *tabela = NULL;
			struct huffman *Arvh = criaHuff(frase, &tabela);

			geraCodigo(Arvh, tabela);
			exibeTabela(tabela);
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
			perror("Erro (ArqTxt):");

		fclose(key);
	}
	else
		perror("Erro (ArqBin):");

	return 0;
}