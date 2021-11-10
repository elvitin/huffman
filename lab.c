#include <stdio.h>

void funcTest(int *x)
{
	printf("(&x) Endereco de x na chamada (%d): [%p]\n",*x, &x);
	printf("(&a) Seu valor x: [%p]\n", x);
	printf("(*x) Oque seu valor guarda: [%d]\n\n", *x);

	if (*x < 5)
	{
		(*x)++;
		funcTest(x);
	}
}


int main (void)
{
	int a = 1;
	
	printf("(main) &a: [%p]\n\n", &a);
	funcTest(&a);
	return 0;
}
