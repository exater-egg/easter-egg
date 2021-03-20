// rename main to parser
#define parser main
#include "table.h"
#include <stdio.h>

int parser () {
    advance();
    parse_table();
    return 0;
}
