#ifndef YY_SKIP_YYWRAP
#include "table.h"
#include <stdio.h>

int main () {
    printf("Linha, Coluna, tamanho, nome do token, lexema\n");
    advance();
    parse_table();
    return 0;
}
#endif
