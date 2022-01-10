/**
 * @file Ficheiro que contém a função principal.
 */

#include <stdio.h>
#include <assert.h>
#include <string.h>

#include "../header/parse.h"
#include "../header/stack.h"

/**
 * \brief Esta é a função principal do programa.
 * @return O 
 */
int main()
{
    char line [10240];
    assert( fgets (line, 10240,stdin) != NULL);
    assert( line [strlen (line) - 1] == '\n');
    parse(line);
    return 0;
}

