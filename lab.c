
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define ASCII_RANGE 256

typedef struct arvh
{
	struct arvh *esq;
	char				 chr;
	int					 frq;
	struct arvh *dir;

} *Arvh;


char *freq (void)
{
	//ASCII_RANGE

	static char *str = {"Vic"};

	printf("[%s]\n", str);

	return str;
}


int main (void)
{
	/*
	for (int i = 0; i < ASCII_RANGE; i++)
		printf("%c\n", i);
	*/

	printf("texto%ctexto\n", 11);
	//printf("texto\ttexto\n");
	return 0;
}
