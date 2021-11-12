#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct huffman
{
	struct huffman *esq;
	int index;
	int frq;
	struct huffman *dir;

} *NoHuff;

#define ASCII_RANGE 256

NoHuff criaNo(NoHuff e, char c, int f, NoHuff d)
{
	NoHuff n = malloc(sizeof(struct huffman));
	n->esq = e;
	n->chr = c;
	n->frq = f;
	n->dir = d;
	return n;
}

void insf (NoHuff A, NoHuff F[], int *m)
{
	int i = *m;
	while (i > 0 && F[i - 1]->frq < A->frq) {

		F[i] = F[i - 1];
		i--;
	}
	F[i] = A;
	(*m)++;
}



NoHuff remf (NoHuff F[], int *m)
{
	if (*m == 0)
		abort();
	
	return F[--(*m)];
}

int *freq (char *s)
{
	//ASCII_RANGE
	int f[ASCII_RANGE];

	int i = 0;
	for (i = 0; i < ASCII_RANGE; i++)
		f[i] = 0;
	
	for (i = 0; s[i] != '\0'; i++)
		f[ s[i] ]++;
	
	return f;
}

NoHuff huffman (char *s)
{
	NoHuff F[ASCII_RANGE];
	int m = 0;
	int *f = freq(s);

	for (int c = 0; c < ASCII_RANGE; c++)
		if (f[c] > 0)
			insf(criaNo(NULL, c, f[c], NULL), F, &m);
		
	while (m > 1)
	{
		NoHuff d = remf(F, &m);
		NoHuff e = remf(F, &m);
		insf(criaNo(e, '-', e->frq + d->frq, d), F, &m);
	}
	return F[0];
}

void exibeh (NoHuff A)
{
	static int n = -1;
	if ( A == NULL )
		return;
	
	n++;

	exibeh(A->dir);

	for (int i = 0; i < 5 * n; i++)
		putchar(' ');
	
	printf("(%c,%d)\n", A->chr, A->frq);

	exibeh(A->esq);
	n--;
}

void exibeFreq (int *f)
{
	for (int i = 0; i < ASCII_RANGE; i++)
		printf("%d[%d]\n", i, f[i]);
	putchar('\n');
}

void codigo (NoHuff A) {

	static char d[ASCII_RANGE], t = -1;

	if (A == NULL)
		return;

	if (A->esq == NULL && A->dir == NULL)
		printf("%c: %.*s\n", A->chr, t + 1, d);
	else
	{
		t++;
		d[t] = '0'; codigo(A->esq);
		d[t] = '1'; codigo(A->dir);
		t--;
	}
}


void tabela (NoHuff A, char *H[])
{
	static char c[ASCII_RANGE], t = -1;
	if (A == NULL)
		return;
	
	if (A->esq == NULL && A->dir == NULL)
		H[A->chr] = strndup(c, t + 1);
	else
	{
		t++;
		c[t] = '0'; tabela(A->esq, H);
		c[t] = '1'; tabela(A->dir, H);
		t--;
	}
}

void comprimir (char *s, NoHuff A)
{
	char *T[ASCII_RANGE];
	int i;
	int c;

	for (c = 0; c < ASCII_RANGE; c++)
		T[c] = NULL;
	tabela(A, T);
	
	for (i = 0; s[i]; i++)
		printf("%s", T[s[i]]);
	
	for (c = 0; c < ASCII_RANGE; c++)
		free(T[c]);
}

void descomprimir (char *d, NoHuff A)
{
	if (A == NULL)
		return;
	
	NoHuff n = A;

	for (int i = 0; d[i]; i++)
	{
		n = (d[i] == '0') ? n->esq : n->dir;

		if (n->esq == NULL && n->dir == NULL) {
			printf("%c", n->chr);
			n = A;
		}
	}

}

int main (void)
{

	int *vet;
	char str[] = {"Abracadabra!"};

	puts(str);

	vet = freq(str);

	exibeFreq(vet);
	

	//exibeh(huffman("Abracadabra!"));
	//codigo(huffman("Abracadabra!"));
	//NoHuff A;
	//comprimir("Abracadraba!", A);

	return 0;
}