#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct arvh
{
	struct arvh *esq;
	char				 chr;
	int					 frq;
	struct arvh *dir;

} *Arvh;

/*

ASCII Table
Dec  = Decimal Value
Char = Character

'5' has the int value 53
if we write '5'-'0' it evaluates to 53-48, or the int 5
if we write char c = 'B'+32; then c stores 'b'


Dec  Char                           Dec  Char     Dec  Char     Dec  Char
---------                           ---------     ---------     ----------
  0  NUL (null)                      32  SPACE     64  @         96  `
  1  SOH (start of heading)          33  !         65  A         97  a
  2  STX (start of text)             34  "         66  B         98  b
  3  ETX (end of text)               35  #         67  C         99  c
  4  EOT (end of transmission)       36  $         68  D        100  d
  5  ENQ (enquiry)                   37  %         69  E        101  e
  6  ACK (acknowledge)               38  &         70  F        102  f
  7  BEL (bell)                      39  '         71  G        103  g
  8  BS  (backspace)                 40  (         72  H        104  h
  9  TAB (horizontal tab)            41  )         73  I        105  i
 10  LF  (NL line feed, new line)    42  *         74  J        106  j
 11  VT  (vertical tab)              43  +         75  K        107  k
 12  FF  (NP form feed, new page)    44  ,         76  L        108  l
 13  CR  (carriage return)           45  -         77  M        109  m
 14  SO  (shift out)                 46  .         78  N        110  n
 15  SI  (shift in)                  47  /         79  O        111  o
 16  DLE (data link escape)          48  0         80  P        112  p
 17  DC1 (device control 1)          49  1         81  Q        113  q
 18  DC2 (device control 2)          50  2         82  R        114  r
 19  DC3 (device control 3)          51  3         83  S        115  s
 20  DC4 (device control 4)          52  4         84  T        116  t
 21  NAK (negative acknowledge)      53  5         85  U        117  u
 22  SYN (synchronous idle)          54  6         86  V        118  v
 23  ETB (end of trans. block)       55  7         87  W        119  w
 24  CAN (cancel)                    56  8         88  X        120  x
 25  EM  (end of medium)             57  9         89  Y        121  y
 26  SUB (substitute)                58  :         90  Z        122  z
 27  ESC (escape)                    59  ;         91  [        123  {
 28  FS  (file separator)            60  <         92  \        124  |
 29  GS  (group separator)           61  =         93  ]        125  }
 30  RS  (record separator)          62  >         94  ^        126  ~
 31  US  (unit separator)            63  ?         95  _        127  DEL

*/

#define ASCII_RANGE 256

Arvh criaNo(Arvh e, char c, int f, Arvh d)
{
	Arvh n = malloc(sizeof(struct arvh));
	n->esq = e;
	n->chr = c;
	n->frq = f;
	n->dir = d;
	return n;
}

void insf (Arvh A, Arvh F[], int *m)
{
	int i = *m;
	while (i > 0 && F[i - 1]->frq < A->frq) {

		F[i] = F[i - 1];
		i--;
	}
	F[i] = A;
	(*m)++;
}



Arvh remf (Arvh F[], int *m)
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

Arvh huffman (char *s)
{
	Arvh F[ASCII_RANGE];
	int m = 0;
	int *f = freq(s);

	for (int c = 0; c < ASCII_RANGE; c++)
		if (f[c] > 0)
			insf(criaNo(NULL, c, f[c], NULL), F, &m);
		
	while (m > 1)
	{
		Arvh d = remf(F, &m);
		Arvh e = remf(F, &m);
		insf(criaNo(e, '-', e->frq + d->frq, d), F, &m);
	}
	return F[0];
}

void exibeh (Arvh A)
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

void codigo (Arvh A) {

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


void tabela (Arvh A, char *H[])
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

void comprimir (char *s, Arvh A)
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

void descomprimir (char *d, Arvh A)
{
	if (A == NULL)
		return;
	
	Arvh n = A;

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
	//Arvh A;
	//comprimir("Abracadraba!", A);

	return 0;
}