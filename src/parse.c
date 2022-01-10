/**
 * @file Ficheiro que contém a função parse.
 */

#include "../header/parse.h"
#include "../header/stack.h"

#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <math.h>

/**
 * \brief função que devolve o token.
 * @param line linha.
 * @param rest_line apontador para o resto da linha.
 * @return O token.
 */
char *get_token (char *line, char **rest_line) {
    char *token;
    token = malloc(sizeof(line));
    while (line[0] == ' ' || line[0] == '\t' || line[0] == '\n') line++;
    int i = 0;
    if(line[0] == '"')
    {
        token[i] = line[0];
        line++;
        i++;
        while(line[0] != '"' && line[0] != '\0')
        {
            token[i] = line[0];
            line++;
            i++;
        }
        token [i] = line[0];
        line++;
    }
    else if(line[0] != '\0')
    {
        while(line[0] != ' ' && line[0] != '\t' && line[0] != '\n'&& line[0] != '\0')
        {
            token[i] = line[0];
            line++;
            i++;
        }
    }
    *rest_line = line+1;
    return token;
}


/** \def st1
  Tipo do elemento do topo da stack.
*/  
#define st1 (stack[size_stack - 1].type)
/** \def st2
  Tipo do segundo elemento topo da stack.
*/ 
#define st2 (stack[size_stack - 2].type)

/**
 * \brief Função que faz a leitura da linha dada no Input.
 * @param line A linha que foi dada de Input.
 * @return O tamanho final da stack.
 */
int parse (char *line)
{
    DADOS stack[10240];
    char **rest;
    rest = malloc(sizeof (line));
    char *token = get_token(line,rest);
    line = *rest;
    tuplo_variavel array_var[26];
    inicializa_array(array_var);
    int size_stack = 0;
    int dentro_array = 0;
    int k = 0;
    for (; k == 0; line = *rest)
    {
        if(**rest == '\0')k = 1;
        switch (*token) {
            case '\\' :
                changenumbers(stack, &size_stack, dentro_array, 2);
                break;
            case '@' :
                changenumbers(stack, &size_stack, dentro_array, 3);
                break;
            case ';' :
                operador_ponto_vir(stack, &size_stack,dentro_array);
                break;
            case ')' :
                operador_fecha_parentes(stack, &size_stack, dentro_array);
                break;
            case '(' :
                operador_abre_parentes(stack,&size_stack,dentro_array);
                break;
            case '+' :
                operador_mais(stack,&size_stack,dentro_array);
                break;
            case '*' :
                operador_vezes(stack,&size_stack,dentro_array);
                break;
            case '/' :
                operador_divisao(stack, &size_stack, dentro_array);
                break;
            case '#' :
                hashtag(stack, &size_stack,dentro_array );
                break;
            case '%' :
                operador_resto(stack, &size_stack,dentro_array);
                break;
            case '&' :
                operador_e(stack, &size_stack,dentro_array);
                break;
            case '|' :
                operador_or(stack, &size_stack,dentro_array);
                break;
            case '^' :
                operador_xor(stack, &size_stack,dentro_array);
                break;
            case '$' :
                operador_dolar(stack, &size_stack,dentro_array);
                break;
            case '_' :
                operador_underscore(stack,&size_stack,dentro_array);
                break;
            case 'l':
                ler_linha(stack, &size_stack,dentro_array);
                break;
            case 'c' :
                converte_char(stack, &size_stack,dentro_array);
                break;
            case 'i' :
                converte_int(stack, &size_stack,dentro_array);
                break;
            case 'f' :
                converte_real(stack, &size_stack,dentro_array);
                break;
            case '=' :
                operador_igual(stack,&size_stack,dentro_array);
                break;
            case '<' :
                operador_menor(stack, &size_stack,dentro_array);
                break;
            case '>':
                operador_bigger(stack,&size_stack,dentro_array);
                break;
            case '!':
                operador_exclamacao(stack, &size_stack,dentro_array);
                break;
            case 'e':
                nxttoken(token, stack, &size_stack, dentro_array);
                break;
            case '?':
                operador_interrogacao(stack, &size_stack,dentro_array);
                break;
            case ':' :
                if (strlen(token) == 2 && token[1] >= 65 && token[1] <= 90 && dentro_array == 0)
                    associa_valor(stack, &size_stack, token[1], variavel_definida(stack, token[0], size_stack), array_var);
                else
                    associa_valor_array(stack[size_stack-1].dados.Array_stack,dentro_array, token [1],array_var);
                break;
            case '[' :
                dentro_array++;
                if (dentro_array == 1)
                    elem_stack_array(stack,&size_stack);
                else
                    push_elem_array(stack[size_stack-1].dados.Array_stack,dentro_array,ARRAY,token);
                break;
            case ']' :
                push_elem_array(stack[size_stack-1].dados.Array_stack,dentro_array,ARRAY,token);
                dentro_array--;
                break;
            case '"' :
                push_string(stack,&size_stack,token,dentro_array);
                break;
            case '~':
                get_out(stack,&size_stack,dentro_array);
                break;
            case ',' :
                tamanho_range (stack, &size_stack, dentro_array);
                break;
            case 't':
                ler_input(stack, &size_stack, dentro_array);
                break;
            case 's':
                operador_s(stack,&size_stack,dentro_array);
                break;
            default :
                if (verifica_numero(token).type == INT)
                    push_numero(stack,&size_stack,token, dentro_array);
                else if (verifica_numero(token).type == REAL)
                    push_numero(stack,&size_stack,token, dentro_array);
                else if (strcmp(token,"-") == 0)
                    operador_menos (stack, &size_stack,dentro_array);
                else if (strcmp(token,"N/") == 0)
                    operadornbarra(stack,&size_stack,dentro_array);
                else if (strcmp(token,"S/") == 0)
                    operadorsbarra(stack,&size_stack,dentro_array);
                else if (strlen(token) == 1 && token[0] >= 65 && token[0] <= 90)
                    add_var_value(stack, &size_stack, token[0], array_var, dentro_array);
                else if (strlen(token) == 1)
                    push_char(stack,&size_stack,token,dentro_array);
                else if (strlen(token) > 1)
                    push_string(stack,&size_stack,token,dentro_array);
        }
        token = get_token(line,rest);
    }
    print_stack(stack,size_stack);
    return 0;
}