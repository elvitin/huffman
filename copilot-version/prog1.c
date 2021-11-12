#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "TAD/huffman.c"


int main (void)
{
    char *frase = "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Maecenas lobortis tristique placerat. Cras ut tincidunt nibh. Aenean eu bibendum odio, nec lobortis orci. Nunc ullamcorper enim et neque iaculis, eget efficitur risus iaculis. Cras vitae fermentum nisl, eget maximus mauris. Quisque elit nunc, elementum a nisl sit amet, ultrices venenatis erat. Nulla sit amet tellus in dolor placerat mattis. Vivamus nec magna euismod, placerat neque et, posuere eros. In placerat augue vel sollicitudin varius. Cras non justo consectetur, euismod ante dictum, tristique orci. Curabitur id mauris id lorem tempor molestie. Morbi rhoncus nisi non porttitor laoreet. Phasellus scelerisque metus tortor, in tincidunt nibh dictum egestas. Integer sed metus consequat, interdum erat ac, faucibus odio. Orci varius natoque penatibus et magnis dis parturient montes, nascetur ridiculus mus. Vestibulum cursus ante dui, non faucibus quam egestas non. Mauris rhoncus, dolor quis fermentum tempus, tellus nisl consequat est, fringilla ullamcorper lectus lorem id arcu. Nunc in sodales justo. Phasellus scelerisque ultricies gravida. Suspendisse fermentum felis vitae libero malesuada luctus. Cras dignissim ultricies nunc, vel fringilla turpis suscipit porta. Ut placerat velit turpis, a mollis nisl eleifend sed. Phasellus sollicitudin, urna at vulputate fermentum, urna mi posuere justo, id dapibus metus tellus at ligula. Morbi non enim odio. Fusce lorem erat, aliquam condimentum eros in, semper pharetra lacus. Morbi porta tortor sem, ac iaculis mi ullamcorper eu. Nam arcu tortor, molestie nec pharetra id, tincidunt sed felis. Aliquam porttitor arcu vitae eros bibendum pretium. Cras dictum faucibus eros a dignissim. Duis et rutrum lorem, et varius ex.";
    int tl=0;
    char tabela[100][50];
    FILE *tab, *fr;
    
    no* huff = criaHuff(frase);
    tab = fopen("tabela.bin", "w");
    fr = fopen("frase.txt", "w");

    tabelaHuff(huff, tabela, &tl);
    
    for(int i=0; i<tl; i++)
        fwrite(tabela[i], sizeof(char), strlen(tabela[i]), tab);
    
    fclose(tab);

    
    return 0;
}