/**
 * @file Ficheiro que contém as funções que trabalham com a stack.
 */

#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <math.h>

#include "../header/stack.h"

/**
 * \brief Dá push a um elemento para o array.
 * @param a array atual.
 * @param elem elemento que queremos adicionar no array.
 */
void push_array (array a, array elem)
{
    switch (elem->elem_type) {
        case INT:
            a[a->size].elem_type = elem->elem_type;
            a[a->size].elem_array.elem_inteiro = elem->elem_array.elem_inteiro;
            break;
        case REAL:
            a[a->size].elem_type = elem->elem_type;
            a[a->size].elem_array.elem_real = elem->elem_array.elem_real;
            break;
        case CHAR:
            a[a->size].elem_type = elem->elem_type;
            a[a->size].elem_array.elem_char = elem->elem_array.elem_char;
            break;
        case VARIAVEL:
            a[a->size].elem_type = elem->elem_type;
            a[a->size].elem_array.elem_variavel = elem->elem_array.elem_variavel;
            break;
        case ARRAY:
            if (a[a->size].elem_type != ARRAY) muda_tipo(a,elem);
            else a[a->size].elem_array.array_dentro = elem;
            break;
        case STRING:
            a[a->size].elem_type = elem->elem_type;
            strcpy(a[a->size].elem_array.elem_string,elem->elem_array.elem_string);
            break;
    }
    a->size++;
}
/**
 * \brief função que adiciona conteudo ao topo stack.
 * @param stack Stack atual.
 * @param N Endereço de memória do comprimento da stack atual.
 * @param d Dado que queremos adcionar á stack.
 * @param x Tipo do dado d.
 * @return Comprimento depois de fazer o push.
 */
int push(DADOS *stack, int *N, DADOS d, TIPO x)
{
    switch (x) {
        case INT :
            stack[(*N)].type = INT;
            stack[(*N)].dados.numero_inteiro = d.dados.numero_inteiro; break;
        case REAL :
            stack[(*N)].type = REAL;
            stack[(*N)].dados.numero_real =  d.dados.numero_real; break;
        case CHAR :
            stack[(*N)].type = CHAR;
            stack[(*N)].dados.caracter = d.dados.caracter; break;
        case STRING :
            stack[(*N)].type = STRING;
            strcpy(stack[(*N)].dados.string,d.dados.string); break;
        case VARIAVEL:
            stack[(*N)].type = VARIAVEL;
            stack[(*N)].dados.variavel = d.dados.variavel; break;
        case ARRAY:
            stack[(*N)].type = ARRAY;
            stack[(*N)].dados.Array_stack = d.dados.Array_stack; break;
    }
    return (*N)++;
}

/**
 * \brief função que muda a troca a posiçao dos number primeiros membros.
 * @param stack Stack atual.
 * @param N Comprimento da stack.
 * @param number nº de valores na stack que iram trocar de posiçao.
 */
void change_nmembers (DADOS *stack, int N, int number)
{
    DADOS d1 = stack[N - 1];
    if (number == 2){
        stack[N - 1] = stack[N - 2];
        stack[N - 2] = d1;
    }
    else{
        stack[N - 1] = stack[N - 3];
        stack[N - 3] = stack[N - 2];
        stack[N - 2] = d1;
    }
}

/**
 * \brief função que troca n elementos de um array.
 * @param a array que queremos trocar os elementos,
 * @param dentro_array quantas vezes estamos dentro de um array.
 * @param n número de elementos que queremos trocar.
 */
void changennumbers_array (array a, int dentro_array, int n)
{
    if(a->dentro_array == dentro_array)
    {
        array a1 = pop_array(a);
        array a2 = pop_array(a);
        if (n == 2)
        {
            push_array(a,a1);
            push_array(a,a2);
        }
        else
        {
            array a3 = pop_array(a);
            push_array(a,a2);
            push_array(a,a1);
            push_array(a,a3);
        }
    }
    else
        changennumbers_array(a[a->size-1].elem_array.array_dentro,dentro_array, n);
}

/**
 * \brief função que troca n elementos.
 * @param stack Stack atual.
 * @param N Endereço do comprimento da stack.
 * @param dentro_array variavel que diz se estamos dentro de um array ou não.
 * @param n numero de elementos que queremos trocar.
 */
void changenumbers (DADOS *stack, int *N, int dentro_array, int n)
{
    if(dentro_array == 0)
        change_nmembers(stack,*N,n);
    else
        changennumbers_array(stack[(*N)-1].dados.Array_stack,dentro_array, n);
}

/**
 * \brief Dá pop a um elemento do array.
 * @param a array ao qual queremos retirar o ultimo elemento.
 * @return O elemento que realizamos o pop.
 */
array pop_array (array a)
{
    array elem = aloca_mem_array();
    elem->elem_type = a[a->size - 1].elem_type;
    switch (elem->elem_type) {
        case INT:
            elem->elem_array.elem_inteiro = a[a->size - 1].elem_array.elem_inteiro;
            break;
        case REAL:
            elem->elem_array.elem_real = a[a->size-1].elem_array.elem_real;
            break;
        case CHAR:
            elem->elem_array.elem_char = a[a->size-1].elem_array.elem_char;
            break;
        case VARIAVEL:
            elem->elem_array.elem_variavel = a[a->size-1].elem_array.elem_variavel;
            break;
        case ARRAY:
            elem = a[a->size-1].elem_array.array_dentro;
            break;
        case STRING:
            strcpy(elem->elem_array.elem_string,a[a->size-1].elem_array.elem_string);
            break;
    }
    a->size--;
    return elem;
}

/**
 * \brief função que retira o elemento do topo da stack.
 * @param stack Stack atual.
 * @param N Endereço de memória do comprimento da stack atual.
 * @return O elemento retirado do topo da stack.
 */
DADOS pop (DADOS *stack, int *N)
{
    DADOS d1;
    d1 = stack[(*N)-1];
    stack[(*N)-1] = stack[*N];
    (*N)--;
    return  d1;
}
/**
 * \brief função que dá pop a um array.
 * @param a array ao qual queremos dar pop.
 * @param dentro_array variavel que diz quantas vezes estamos dentro de um array.
 */
void operador_pop (array a, int dentro_array)
{
    if(a->dentro_array == dentro_array)
        pop_array(a);
    else
        operador_pop(a[a->size-1].elem_array.array_dentro,dentro_array);
}
/**
 * função que decide o que vai fazer quando lemos o char ';'
 * @param stack Stack atual
 * @param N Endereço de memória do comprimento da stack atual.
 * @param dentro_array variavel que diz se estamos dentro de um array ou não.
 */
void operador_ponto_vir (DADOS *stack, int *N, int dentro_array)
{
    if (dentro_array == 0)
        pop(stack,N);
    else
        operador_pop(stack[(*N)-1].dados.Array_stack,dentro_array);
}

/**
 * \brief função que remove um elemento da stack dada a sua posição.
 * @param stack stack atual.
 * @param N Endereço do comprimento da stack atual.
 * @param pos Posição que queremos remover.
 */
void remove_elem (DADOS *stack, int *N, int pos)
{
    int i;
    for (i = pos;i < (*N);i++)
    {
        stack[i] = stack[i+1];
    }
    (*N)--;
}

/**
 * \brief Função que soma os 2 elementos no topo da Stack.
 * No topo da Stack fica o resultado da soma.
 * @param stack Stack atual.
 * @param N Endereço de memória do comprimento da stack atual.
 */
void soma (DADOS *stack, int *N)
{
    DADOS d1;
    DADOS d2;
    d1 = pop(stack, N);
    d2 = pop(stack, N);
    push_resultado (dados_variavel (d2) + dados_variavel (d1),stack,N);
}

/**
 * \brief função que subtrai os 2 elementos no topo da Stack.
 * No topo da Stack fica o resultado da subtração.
 * @param stack Stack atual.
 * @param N Endereço de memória do comprimento da stack atual.
 */
void subtracao (DADOS *stack, int *N)
{
    DADOS d1;
    DADOS d2;
    d1 = pop(stack, N);
    d2 = pop(stack, N);
    push_resultado (dados_variavel (d2)-dados_variavel (d1),stack,N);
}

/**
 * \brief função que multiplica os 2 elementos no topo da Stack.
 * No topo da Stack fica o resultado da multiplicação.
 * @param stack Stack atual.
 * @param N Endereço de memória do comprimento da stack atual.
 */
void multiplicacao (DADOS *stack, int *N)
{
    DADOS d1;
    DADOS d2;
    d1 = pop(stack, N);
    d2 = pop(stack, N);
    push_resultado (dados_variavel (d2)*dados_variavel (d1),stack,N);
}

/**
 * \brief função que eleva o penultimo elemento da Stack ao ultimo.
 * No topo da Stack fica o resultado da exponenciação.
 * @param stack Stack atual.
 * @param N Endereço de memória do comprimento da stack atual.
 */
void expoente (DADOS *stack, int *N)
{
    DADOS d1;
    DADOS d2;
    d1 = pop(stack, N);
    d2 = pop(stack, N);
    push_resultado (pow(dados_variavel (d2),dados_variavel (d1)),stack,N);
}

/**
 * \brief função que divide o penultimo elemento da Stack pelo ultimo.
 * No topo da Stack fica o resultado da divisão.
 * @param stack Stack atual.
 * @param N Endereço de memória do comprimento da stack atual.
 * @param tipo1 tipo do elemento no topo da Stack.
 * @param tipo2 tipo do penultimo elemento da Stack.
 */
void divisao (DADOS *stack, int *N, TIPO tipo1, TIPO tipo2)
{
    DADOS d1;
    DADOS d2;
    d1 = pop(stack, N);
    d2 = pop(stack, N);
    if (tipo1 == INT && tipo2 == INT)
    {
        d2.dados.numero_inteiro /= d1.dados.numero_inteiro;
        push(stack,N,d2,INT);
    }
    else
        push_resultado (dados_variavel (d2)/dados_variavel (d1),stack,N);
}

/**
 * \brief função que calcula o resto da divisão entre o penultimo elemento da Stack e o ultimo.
 * No topo da Stack fica o resultado da divisão.
 * @param stack Stack atual.
 * @param N Endereço de memória do comprimento da stack atual.
 */
void resto (DADOS *stack, int *N)
{
    DADOS d1;
    DADOS d2;
    d1 = pop(stack, N);
    d2 = pop(stack, N);
    d2.dados.numero_inteiro %= d1.dados.numero_inteiro;
    push(stack,N,d2,INT);
}

/**
 * \brief função que aplica a operação & ao penultimo e ultimo elemento da Stack.
 * Mais aprofundado and, compara os bits dos numeros binários correspondente. Caso ambos os bits sejam 1 dá 1 mas caso um deles seja 0 dá 0.
 * No topo da Stack fica o decimal correspondente ao binário a que deu origem depois de efetuadas as operações.
 * @param stack Stack atual.
 * @param N Endereço de memória do comprimento da stack atual.
 */
void and (DADOS *stack, int *N)
{
    DADOS d1;
    DADOS d2;
    d1 = pop(stack, N);
    d2 = pop(stack, N);
    d2.dados.numero_inteiro &= d1.dados.numero_inteiro;
    push(stack,N,d2,INT);
}

/**
 * \brief função que aplica a operação | ao penultimo e ultimo elemento da Stack.
 * Mais aprofundado or, compara os bits dos numeros binários correspondente. Caso ambos os bits sejam 0 dá 0 mas caso um deles seja 1 dá 1.
 * No topo da Stack fica o decimal correspondente ao binário a que deu origem depois de efetuadas as operações.
 * @param stack Stack atual.
 * @param N Endereço de memória do comprimento da stack atual.
 */
void or (DADOS *stack, int *N)
{
    DADOS d1;
    DADOS d2;
    d1 = pop(stack, N);
    d2 = pop(stack, N);
    d2.dados.numero_inteiro |= d1.dados.numero_inteiro;
    push(stack,N,d2,INT);
}

/**
 * \brief função que aplica a operação ^ ao penultimo e ultimo elemento da Stack.
 * Mais aprofundado xor, compara os bits dos numeros binários correspondente. Caso os bits sejam diferentes dá 1 caso contrário dá 0.
 * No topo da Stack fica o decimal correspondente ao binário a que deu origem depois de efetuadas as operações.
 * @param stack Stack atual.
 * @param N Endereço de memória do comprimento da stack atual.
 */
void xor (DADOS *stack, int *N)
{
    DADOS d1;
    DADOS d2;
    d1 = pop(stack, N);
    d2 = pop(stack, N);
    d2.dados.numero_inteiro ^= d1.dados.numero_inteiro;
    push(stack,N,d2,INT);
}

/**
 * \brief função que incrementa o ultimo elemento da Stack.
 * No topo da Stack fica o resultado da incrementação.
 * @param stack Stack atual.
 * @param N Endereço de memória do comprimento da stack atual.
 * @param tipo1 tipo do elemento no topo da Stack.
 */
void incrementa (DADOS *stack, int *N, TIPO tipo1)
{
    DADOS d1;
    d1 = pop(stack, N);
    switch (tipo1) {
        case INT:
            push_resultado(dados_variavel(d1)+1,stack,N);;
            break;
        case REAL:
            push_resultado(dados_variavel(d1)+1,stack,N);
            break;
        case CHAR:
            d1.dados.caracter+=1;
            push(stack,N,d1,CHAR);
            break;
        case VARIAVEL:
            push_resultado(double_var(d1.dados.variavel)+1,stack,N);
            break;
        case STRING:
            break;
        case ARRAY:
            break;
    }
}

/**
 * \brief função que drecrementa o ultimo elemento da Stack.
 * No topo da Stack fica o resultado da decrementação.
 * @param stack Stack atual.
 * @param N Endereço de memória do comprimento da stack atual.
 * @param tipo1 tipo do elemento no topo da Stack.
 */
void decrementa (DADOS *stack, int *N, TIPO tipo1)
{
    DADOS d1;
    d1 = pop(stack, N);
    switch (tipo1) {
        case INT:
            push_resultado(dados_variavel(d1)-1,stack,N);;
            break;
        case REAL:
            push_resultado(dados_variavel(d1)-1,stack,N);
            break;
        case CHAR:
            d1.dados.caracter-=1;
            push(stack,N,d1,CHAR);
            break;
        case VARIAVEL:
            push_resultado(double_var(d1.dados.variavel)-1,stack,N);
            break;
        case STRING:
            break;
        case ARRAY:
            break;
    }
}
/**
 * \brief função que verifica se os 2 primeiros valores da stack sao iguais.
 * No topo da stack fica 1 caso os 2 valores sejam iguais, 0 caso contrario.
 * @param stack Stack atual.
 * @param N Endereço de memória do comprimento da stack atual.
 */
void equal (DADOS *stack, int *N)
{
    DADOS d1,d2;
    d1=pop(stack, N);
    d2=pop(stack, N);
    d1.dados.numero_inteiro= dados_variavel(d1) == dados_variavel(d2);
    push(stack, N, d1,INT);
}
/**
 * \brief função que verifica se o primeiro elemento da stack e maior que o segundo.
 * No topo da stack fica 1 caso o o primeiro valor seja maior, 0 caso contrario.
 * @param stack Stack atual.
 * @param N Endereço de memória do comprimento da stack atual.
 */
void bigger (DADOS *stack, int *N)
{
    DADOS d1,d2;
    d1=pop(stack, N);
    d2=pop(stack, N);
    d1.dados.numero_inteiro = dados_variavel(d2)>dados_variavel(d1);
    push(stack, N, d1,INT);
}
/**
 * \brief função que verifica se o primeiro elemento da stack e menor que o segundo.
 * No topo da stack fica 1 caso o o primeiro valor seja menor, 0 caso contrario.
 * @param stack Stack atual.
 * @param N Endereço de memória do comprimento da stack atual.
 */
void minor (DADOS *stack, int *N)
{
    DADOS d1,d2;
    d1=pop(stack, N);
    d2=pop(stack, N);
    d1.dados.numero_inteiro = dados_variavel(d2)<dados_variavel(d1);
    push(stack, N, d1,INT);
}
/**
 * \brief função que inverte o valor do primeiro elemento da stack.
 * No topo da stack fica 1 caso o o primeiro valor seja 0, 0 caso contrario.
 * @param stack Stack atual.
 * @param N Endereço de memória do comprimento da stack atual.
 */
void change_bool (DADOS *stack, int *N)
{
    DADOS d1;
    d1=pop(stack, N);
    d1.dados.numero_inteiro= dados_variavel(d1) == 0;
    push(stack, N, d1,INT);
}

/**
 * \brief realiza a operação do char '&' dentro de um array.
 * @param a array que queremos operar.
 * @param dentro_array variavel que diz o quão dentro estamos de um array.
 */
void log_e_array (array a, int dentro_array)
{
    if(a->dentro_array == dentro_array)
    {
        array a1 = pop_array(a);
        array a2 = pop_array(a);
        if(dados_array(a1) != 0 && dados_array(a2) != 0)
            push_array(a,a1);
        else
        {
            a1->elem_array.elem_inteiro = 0;
            a1->elem_type = INT;
            push_array(a,a1);
        }
    }
    else
        log_e_array(a[a->size-1].elem_array.array_dentro,dentro_array);
}

/**
 * \brief função que atribuir o valor lógico & aos dois elementos do topo da stack.
 * No topo da stack fica o valor lógico 0 caso um dos elementos seja falso e caso ambos sejam verdadeiros dá push do penultimo elemento.
 * @param stack Stack atual.
 * @param N Endereço de memória do comprimento da stack atual.
 * @param dentro_array variavel que diz o quão dentro estamos de um array.
 */
void logica_e (DADOS *stack, int *N, int dentro_array)
{
    if(dentro_array == 0)
    {
        DADOS d1,d2;
        d1=pop(stack, N);
        d2=pop(stack, N);
        if (dados_variavel(d1) != 0 && dados_variavel(d2) != 0)
            push(stack,N,d1,d1.type);
        else
        {
            d1.dados.numero_inteiro = 0;
            push(stack,N,d1,INT);
        }
    }
    else
        log_e_array(stack[(*N)-1].dados.Array_stack,dentro_array);
}

/**
 * \brief realiza a operação do char '|' dentro de um array.
 * @param a array que queremos operar.
 * @param dentro_array variavel que diz o quão dentro estamos de um array.
 */
void log_ou_array (array a, int dentro_array)
{
    if(a->dentro_array == dentro_array)
    {
        array a1 = pop_array(a);
        array a2 = pop_array(a);
        if(dados_array(a2) != 0)
            push_array(a,a2);
        else
            push_array(a,a1);
    }
    else
        log_ou_array(a[a->size-1].elem_array.array_dentro,dentro_array);
}

/**
 * \brief função que atribuir o valor lógico | aos dois elementos do topo da stack.
 * No topo da stack fica o valor lógico d2 caso sejam ambos diferentes de 0, caso contrário fica o d1.
 * @param stack Stack atual.
 * @param N Endereço de memória do comprimento da stack atual.
 * @param dentro_array variavel que diz o quão dentro estamos de um array.
 */
void logica_ou (DADOS *stack, int *N, int dentro_array)
{
    if(dentro_array == 0)
    {
        DADOS d1,d2;
        d1=pop(stack, N);
        d2=pop(stack, N);
        if (dados_variavel(d2) != 0)
            push(stack,N,d2,d2.type);
        else
            push(stack,N,d1,d1.type);
    }
    else
        log_ou_array(stack[(*N)-1].dados.Array_stack,dentro_array);
}

/**
 * função que verifica se uma string é maior que a outra.
 * @param s1 string que vamos se é maior.
 * @param s2 string de comparação.
 * @return 1 se s1 > s2 e 0 caso contrário.
 */
int minor_strings (char *s1,char *s2)
{
    int i;
    for (i = 0; s1[i] != '\0' && s2[i] != '\0'; i++)
    {
        if (s1[i] > s2[i]) return 0;
        else if (s1[i] < s2[i]) return 1;
    }
    return 0;
}

/**
 * \brief realiza a operação do char '<' dentro de um array.
 * @param a array que queremos operar.
 * @param dentro_array variavel que diz o quão dentro estamos de um array.
 */
void log_men_array (array a, int dentro_array)
{
    if(a->dentro_array == dentro_array)
    {
        array a1 = pop_array(a);
        array a2 = pop_array(a);
        if (a1->elem_type == STRING && a2->elem_type == STRING)
        {
            if (minor_strings(a2->elem_array.elem_string,a1->elem_array.elem_string) == 1)
                push_array(a,a2);
            else
                push_array(a,a1);
        }
        else
        {
            double x = dados_array(a1);
            double y = dados_array(a2);
            if (x > y)
                push_array(a,a2);
            else
                push_array(a,a1);
        }
    }
    else
        log_men_array(a[a->size-1].elem_array.array_dentro,dentro_array);
}

/**
 * \brief função que dá o menor dos dois elementos do topo da stack.
 * @param stack Stack atual.
 * @param N Endereço de memória do comprimento da stack atual.
 * @param dentro_array variavel que diz o quão dentro estamos de um array.
 */
void logica_menor (DADOS *stack, int *N, int dentro_array)
{
    if (dentro_array == 0)
    {
        DADOS d1,d2;
        d1=pop(stack, N);
        d2=pop(stack, N);
        if(d1.type == STRING && d2.type ==STRING)
        {
            if (minor_strings(d2.dados.string,d1.dados.string) == 0)
                push(stack,N,d1,STRING);
            else
                push(stack,N,d2,STRING);
        }
        else
        {
            if (dados_variavel(d1) > dados_variavel(d2))
                push(stack,N,d2,d2.type);
            else
                push(stack,N,d1,d1.type);
        }
    }
    else
        log_men_array(stack[(*N)-1].dados.Array_stack,dentro_array);
}

/**
 * função que verifica se uma string é maior que a outra.
 * @param s1 string que vamos se é maior.
 * @param s2 string de comparação.
 * @return 1 se s1 > s2 e 0 caso contrário.
 */
int bigger_strings (char *s1,char *s2)
{
    int i;
    for (i = 0; s1[i] != '\0' && s2[i] != '\0'; i++)
    {
        if (s1[i] > s2[i]) return 1;
        else if (s1[i] < s2[i]) return 0;
    }
    return 0;
}

/**
 * \brief realiza a operação do char '>' dentro de um array.
 * @param a array que queremos operar.
 * @param dentro_array variavel que diz o quão dentro estamos de um array.
 */
void log_mai_array (array a, int dentro_array)
{
    if(a->dentro_array == dentro_array)
    {
        array a1 = pop_array(a);
        array a2 = pop_array(a);
        if (a1->elem_type == STRING && a2->elem_type == STRING)
        {
            if (bigger_strings(a2->elem_array.elem_string,a1->elem_array.elem_string) == 1)
                push_array(a,a2);
            else
                push_array(a,a1);
        }
        else
        {
            double x = dados_array(a1);
            double y = dados_array(a2);
            if (x < y)
                push_array(a,a2);
            else
                push_array(a,a1);
        }
    }
    else
        log_mai_array(a[a->size-1].elem_array.array_dentro,dentro_array);
}

/**
 * \brief função que dá o maior dos dois elementos do topo da stack.
 * @param stack Stack atual.
 * @param N Endereço de memória do comprimento da stack atual.
 * @param dentro_array variavel que diz o quão dentro estamos de um array.
 */
void logica_maior (DADOS *stack, int *N, int dentro_array)
{
    if (dentro_array == 0)
    {
        DADOS d1,d2;
        d1=pop(stack, N);
        d2=pop(stack, N);
        if (d1.type == STRING && d2.type == STRING)
        {
            if (minor_strings(d2.dados.string,d1.dados.string) == 0)
                push(stack,N,d2,STRING);
            else
                push(stack,N,d1,STRING);
        }
        else
        {
            if (dados_variavel(d1) < dados_variavel(d2))
                push(stack,N,d2,d2.type);
            else
                push(stack,N,d1,d1.type);
        }
    }
    else
        log_mai_array(stack[(*N)-1].dados.Array_stack,dentro_array);
}

/**
 * \brief função que dá pop aos 3 elementos no topo da stack e realiza o if then else.
 * @param stack Stack atual.
 * @param N Endereço de memória do comprimento da stack atual.
 */
void if_then_else (DADOS *stack, int *N)
{
    DADOS d1,d2,d3;
    d1=pop(stack, N);
    d2=pop(stack, N);
    d3=pop(stack,N);
    if (dados_variavel(d3) != 0)
        push(stack,N,d2,d2.type);
    else
        push(stack,N,d1,d1.type);
}

/**
 * \brief funçao que vai buscar o array e converte o elemento do topo do array para Int.
 * @param a array atual.
 * @param dentro_array variavel que diz em que grau esta o array.
 */
void converte_int_array (array a, int dentro_array)
{
    if(a->dentro_array == dentro_array)
    {
        array a1 = pop_array(a);
        a1->elem_array.elem_inteiro = dados_array(a1);
        a1->elem_type = INT;
        push_array(a,a1);
    }
    else
        converte_int_array(a[a->size-1].elem_array.array_dentro,dentro_array);
}

/**
 * \brief função que converte o elemento do topo da stack para Inteiro.
 * @param stack Stack atual.
 * @param N Endereço de memória do comprimento da stack atual.
 * @param dentro_array variavel que diz o quão dentro estamos de um array.
 */
void converte_int (DADOS *stack, int *N, int dentro_array)
{
    if (dentro_array == 0)
    {
        DADOS elem;
        elem = pop(stack,N);
        elem.dados.numero_inteiro = dados_variavel(elem);
        push(stack,N,elem, INT);
    }
    else
        converte_int_array(stack[(*N)-1].dados.Array_stack,dentro_array);
}

/**
 * \brief funçao que vai buscar o array e converte o elemento do topo do array para Real.
 * @param a array atual.
 * @param dentro_array variavel que diz em que grau esta o array.
 */
void converte_double_array (array a, int dentro_array)
{
    if(a->dentro_array == dentro_array)
    {
        array a1 = pop_array(a);
        a1->elem_array.elem_real = dados_array(a1);
        a1->elem_type = REAL;
        push_array(a,a1);
    }
    else
        converte_double_array(a[a->size-1].elem_array.array_dentro,dentro_array);
}

/**
 * \brief função que converte o elemento do topo da stack para Real.
 * @param stack Stack atual.
 * @param N Endereço de memória do comprimento da stack atual.
 * @param dentro_array variavel que diz o quão dentro estamos de um array.
 */
void converte_real (DADOS *stack, int *N, int dentro_array)
{
    if (dentro_array == 0)
    {
        DADOS elem;
        elem = pop(stack,N);
        elem.dados.numero_real = dados_variavel(elem);
        push(stack,N,elem, REAL);
    }
    else
        converte_double_array(stack[(*N)-1].dados.Array_stack,dentro_array);
}

/**
 * \brief funçao que vai buscar o array e converte o elemento do topo do array para Char.
 * @param a array atual.
 * @param dentro_array variavel que diz em que grau esta o array.
 */
void converte_char_array (array a, int dentro_array)
{
    if(a->dentro_array == dentro_array)
    {
        array a1 = pop_array(a);
        array d = aloca_mem_array();
        d->elem_type = CHAR;
        d->elem_array.elem_char = dados_array(a1);
        push_array(a,d);
    }
    else
        converte_char_array(a[a->size-1].elem_array.array_dentro,dentro_array);
}

/**
 * \brief função que converte o elemento do topo da stack para Char.
 * @param stack Stack atual.
 * @param N Endereço de memória do comprimento da stack atual.
 * @param dentro_array variavel que diz o quão dentro estamos de um array.
 */
void converte_char (DADOS *stack, int *N, int dentro_array)
{
    if (dentro_array == 0)
    {
        DADOS elem;
        elem = pop(stack,N);
        elem.dados.caracter = dados_variavel(elem);
        push(stack, N, elem, CHAR);
    }
    else
        converte_char_array(stack[(*N)-1].dados.Array_stack,dentro_array);
}

/**
 * \brief Função para ler a linha.
 * @param stack Stack atual.
 * @param N Endereço do comprimento atual da stack.
 * @param dentro_array variavel que diz o quão dentro estamos de um array.
 */
void ler_linha (DADOS *stack, int *N, int dentro_array)
{
    DADOS elem;
    assert(fgets (elem.dados.string, 200,stdin) != NULL);
    assert(elem.dados.string [strlen (elem.dados.string) - 1] == '\n');
    move_pointer_frente(elem.dados.string);
    elem.dados.string[0] = '"';
    elem.dados.string[strlen(elem.dados.string)-1] = '"';
    push_string(stack,N,elem.dados.string,dentro_array);
}
/**
 * \brief Inicia arrays que vão representar variaveis.
 * @param var_d Array das variaveis reais.
 * @param var_c Array das variaveis chars.
 */
void inicializa_array (tuplo_variavel *array_var)
{
    int i;
    int val = 10;
    int val_a = 0;
    for (i = 65; i <= 90; i++)
    {
        array_var[i].indentificacao = i;
        if(i >= 65 && i <= 70)
        {
            array_var[i-65].tipo = INTEIRO;
            array_var[i-65].tipo_variavel.variavel_int = val;
            val++;
        }
        else if (i >= 88 && i <= 90)
        {
            array_var[i-65].tipo = INTEIRO;
            array_var[i-65].tipo_variavel.variavel_int = val_a;
            val_a++;
        }
        else if (i == 78)
        {
            array_var[i-65].tipo = CARACTER;
            array_var[i-65].tipo_variavel.variavel_char = '\n';
        }
        else if (i == 83)
        {
            array_var[i-65].tipo = CARACTER;
            array_var[i-65].tipo_variavel.variavel_char = ' ';
        }
    }
}
/**
 * \brief Converte o tipo de um elemento da stack em tipo de variavel.
 * @param d Elemnto que queremos mudar de tipo.
 * @return Tipo da variavel.
 */
TIPO_VARIAVEL converte_tipo (TIPO d)
{
    switch (d)
    {
        case INT: return INTEIRO;
        case REAL: return DOUBLE;
        case CHAR: return CARACTER;
        case STRING: return TEXTO;
        default:break;
    }
    return INTEIRO;
}
/**
 * \brief Atualiza o valor da variavel no array
 * @param var_d Array das variaveis reais.
 * @param var_c Array das variaveis chars.
 * @param c Variavel que queremos alterar.
 * @param d Valor final da variavel.
 */
void atualiza_array (tuplo_variavel *array_var, char c, DADOS d)
{
    array_var[c-65].tipo = converte_tipo(d.type);
    switch (array_var[c-65].tipo)
    {
        case INTEIRO:
            array_var[c-65].tipo_variavel.variavel_int = d.dados.numero_inteiro;
            break;
        case DOUBLE:
            array_var[c-65].tipo_variavel.variavel_real = d.dados.numero_real;
            break;
        case CARACTER:
            array_var[c-65].tipo_variavel.variavel_char = d.dados.caracter;
            break;
        case TEXTO:
            strcpy(array_var[c-65].tipo_variavel.variavel_string,d.dados.string);
            break;
    }
}

/**
 * \brief Converte um elemento da stack em variavel.
 * @param d Elemento da stack.
 * @return Respetiva variavel.
 */
tuplo_variavel converte_dados_variavel (DADOS d)
{
    if (d.type == INT)
        d.dados.variavel.tipo_variavel.variavel_int = d.dados.numero_inteiro;
    else if (d.type == REAL)
        d.dados.variavel.tipo_variavel.variavel_real = d.dados.numero_real;
    else if (d.type == CHAR)
        d.dados.variavel.tipo_variavel.variavel_char = d.dados.caracter;
    else if (d.type == STRING)
        strcpy(d.dados.variavel.tipo_variavel.variavel_string,d.dados.string);
    d.dados.variavel.tipo = converte_tipo(d.type);
    return d.dados.variavel;
}

/**
 * \brief Vai buscar o valor do topo da stack e associa a uma variavel e da push com tipo variavel.
 * @param stack Stack atual.
 * @param N Endereço do comprimento da STack atual.
 * @param d1 Valor que estava no topo da stack.
 * @param va Nome da variavel.
 */
void push_variavel (DADOS *stack, int *N, DADOS d1, char va)
{
    d1.dados.variavel = converte_dados_variavel (d1);
    d1.dados.variavel.indentificacao = va;
    push(stack,N,d1,VARIAVEL);
}

/**
 * \brief transforma um tipo de variavel em tipo de um elemento da stack/array.
 * @param var variavel que contem o tipo que queremos mudar.
 * @return Tipo de um elemento da stack/array.
 */
TIPO converte_tipo_var (tuplo_variavel var)
{
    switch (var.tipo)
    {
        case INTEIRO:
            return INT;
        case DOUBLE:
            return REAL;
        case CARACTER:
            return CHAR;
        case TEXTO:
            return STRING;
    }
    return INT;
}

/**
 * \brief Dá push a uma variavel que n está definida na stack.
 * @param stack Stack atual.
 * @param N Endereço do comprimento da stack.
 * @param c Nome da variavel.
 * @param array_var Array correspondente ás variaveis atuais;
 */
void push_variavel_omissao (DADOS *stack, int *N, char c, tuplo_variavel *array_var)
{
    DADOS elem;
    elem.type = converte_tipo_var(array_var[c-65]);
    switch (array_var[c-65].tipo)
    {
        case INTEIRO:
            elem.dados.numero_inteiro = array_var[c-65].tipo_variavel.variavel_int;
            break;
        case DOUBLE:
            elem.dados.numero_real = array_var[c-65].tipo_variavel.variavel_real;
            break;
        case TEXTO:
            strcpy(elem.dados.string,array_var[c-65].tipo_variavel.variavel_string);
            break;
        case CARACTER:
            elem.dados.caracter = array_var[c-65].tipo_variavel.variavel_char;
            break;
    }
    push(stack,N,elem,elem.type);
}
/**
 * \brief função que atualiza o valor de uma variavel, dando o elemento no topo da stack.
 * @param stack Stack atual.
 * @param pos Posição da variavel que queremos atualizar.
 * @param d1 Elemento do topo da stack que queremos atualizar na variavel.
 */
void atualiza_valor (DADOS *stack, int pos, DADOS d1)
{
    if (d1.type == INT)
        stack[pos].dados.variavel.tipo_variavel.variavel_int = d1.dados.numero_inteiro;
    else if (d1.type == REAL)
        stack[pos].dados.variavel.tipo_variavel.variavel_real = d1.dados.numero_real;
    else if (d1.type == CHAR)
        stack[pos].dados.variavel.tipo_variavel.variavel_char = d1.dados.caracter;
}

/**
 * \brief Verifica se uma variavel está definida na Stack até ao momento.
 * @param stack Stack atual.
 * @param s Variavel
 * @param N ENdereço do comprimento da stack.
 * @return 1 se estiver definida, a posicao caso contrário.
 */
int variavel_definida (DADOS *stack, char c, int N)
{
    int i;
    for (i = 0; i < N; i++)
        if (stack[i].type == VARIAVEL && c == stack[i].dados.variavel.indentificacao)
            return i;
    return (-1);
}
/**
 * \brief função que move o pointer de uma string para a frente.
 * @param s string que queremos alterar.
 * @return string final.
 */
char *move_pointer (char *s)
{
    int i;
    for(i = 0; s[i] != '\0'; i++)
    {
        s[i] = s[i+1];
    }
    return s;
}
/**
 * função que dá print a uma string.
 * @param s string que queremos dar print.
 */
void print_string(char *s)
{
    s[strlen(s)-1] = '\0';
    move_pointer(s);
    printf("%s",s);
}
/**
 * \brief função que dá print a uma variavel.
 * @param v variavel á qual queremos dar print.
 */
void print_variavel (tuplo_variavel v)
{
    switch (v.tipo){
        case INTEIRO:
            printf("%ld",v.tipo_variavel.variavel_int);
            break;
        case DOUBLE:
            printf("%.6g",v.tipo_variavel.variavel_real);
            break;
        case CARACTER:
            printf("%c",v.tipo_variavel.variavel_char);
            break;
        case TEXTO:
            print_string(v.tipo_variavel.variavel_string);
            break;
    }
}
/**
 * \brief função que dá print a um elemento do tipo ARRAY
 * @param Array respetivo elemento que queremos dar print
 */
void print_array (array Array)
{
    int i;
    int dentro_array = Array->dentro_array;
    for (i = 0; i < Array->size; i++)
    {
        switch (Array[i].elem_type) {
            case ARRAY:
                if (Array[i].dentro_array > dentro_array)
                    print_array(Array[i].elem_array.array_dentro);
                break;
            case INT:
                printf("%ld",Array[i].elem_array.elem_inteiro);
                break;
            case REAL:
                printf("%g" ,Array[i].elem_array.elem_real);
                break;
            case CHAR:
                printf("%c" ,Array[i].elem_array.elem_char);
                break;
            case VARIAVEL:
                print_variavel(Array[i].elem_array.elem_variavel);
                break;
            case STRING:
                print_string(Array[i].elem_array.elem_string);
                break;
        }
    }
}

/**
 * \brief função que dá print á stack final.
 * @param stack Stack final.
 * @param N Comprimento da stack.
 */
void print_stack(DADOS *stack, int N)
{
    int i;
    for (i = 0; i < N; i++)
    {
        switch (stack[i].type){
            case INT   :
                printf("%ld", stack[i].dados.numero_inteiro);
                break;
            case REAL  :
                printf("%.6g", stack[i].dados.numero_real);
                break;
            case CHAR  :
                printf("%c", stack[i].dados.caracter);
                break;
            case STRING:
                print_string(stack[i].dados.string);
                break;
            case VARIAVEL:
                print_variavel(stack[i].dados.variavel);
                break;
            case ARRAY:
                print_array(stack[i].dados.Array_stack);
                break;
        }
    }
    putchar('\n');
}

/**
 * \brief função que converte um elemento da stack para double.
 * @param d Dado que queremos mudar de tipo.
 */
double dados_variavel (DADOS d)
{
    if (d.type == INT)
        return d.dados.numero_inteiro;
    else if (d.type == REAL)
        return d.dados.numero_real;
    else if (d.type == CHAR)
        return d.dados.caracter;
    else if (d.type == STRING)
    {
        char *sobra;
        d.dados.string[strlen(d.dados.string) - 1] = '\0';
        move_pointer(d.dados.string);
        return (strtod(d.dados.string, &sobra));
    }
    else if (d.type == VARIAVEL && d.dados.variavel.tipo == INTEIRO)
        return d.dados.variavel.tipo_variavel.variavel_int;
    else if (d.type == VARIAVEL && d.dados.variavel.tipo == DOUBLE)
        return d.dados.variavel.tipo_variavel.variavel_real;
    else if (d.type == ARRAY && d.dados.Array_stack->size > 2)
        return 1;
    return 0;
}

/**
 * \brief função dá push a um resultado dependendo se ele for um real ou um inteiro.
 * @param resultado Variavel que queremos dar push.
 * @param stack Stack atual.
 * @param N Endereço da STack atual.
 */
void push_resultado (double resultado, DADOS *stack, int *N)
{
    DADOS d;
    if (resultado == floor(resultado))
    {
        d.dados.numero_inteiro=resultado;
        push(stack,N,d,INT);
    }
    else
    {
        d.dados.numero_real=resultado;
        push(stack,N,d, REAL);
    }
}

/**
 * \brief Associa o valor do topo da stack a uma variavel.
 * @param stack Stack atual.
 * @param N Endereço do comprimento da stack.
 * @param c Nome da variavel.
 * @param pos Pos aonde  a variavel está definida, -1 caso não esteja.
 * @param array_var Array dos valores das variaveis definidas por omissão.
 */
void associa_valor (DADOS *stack, int *N, char c, int pos, tuplo_variavel *array_var)
{
    DADOS elem;
    elem = pop(stack,N);
    if (pos != -1)
        atualiza_valor(stack,pos,elem);
    else
        push_variavel(stack,N,elem,c);
    atualiza_array(array_var,c,elem);
}

/**
 * \brief converte um elemento de um array para um elemento da stack.
 * @param a Array que queremos converter.
 * @return resultado da conversao.
 */
DADOS convert_array_dados (array a)
{
    DADOS elem;
    elem.type=a->elem_type;
    switch (elem.type)
    {
        case INT:
            elem.dados.numero_inteiro = a->elem_array.elem_inteiro;
            break;
        case REAL:
            elem.dados.numero_real = a->elem_array.elem_real;
            break;
        case CHAR:
            elem.dados.caracter = a->elem_array.elem_char;
            break;
        case VARIAVEL:
            elem.dados.variavel = a->elem_array.elem_variavel;
            break;
        case STRING:
            strcpy(elem.dados.string,a->elem_array.elem_string);
            break;
        case ARRAY:
            elem.dados.Array_stack = a->elem_array.array_dentro;
            break;
    }
    return elem;
}

/**
 * \brief converte um elemento de um array para variavel.
 * @param a elemento que queremos converter.
 */
void converte_dados_var (array a)
{
    if (a->elem_type == INT)
        a->elem_array.elem_variavel.tipo_variavel.variavel_int = a->elem_array.elem_inteiro;
    else if (a->elem_type == REAL)
        a->elem_array.elem_variavel.tipo_variavel.variavel_real = a->elem_array.elem_real;
    else if (a->elem_type == CHAR)
        a->elem_array.elem_variavel.tipo_variavel.variavel_char = a->elem_array.elem_char;
}

/**
 * \brief função que associa um valor de um array a uma variavel.
 * @param a array no qual queremos adicionar a variavel.
 * @param dentro_array variavel que diz se estamos no array certo ou não.
 * @param c char que corresponde á variavel.
 * @param array_var array das variaveis atual.
 */
void associa_valor_array (array a, int dentro_array, char c, tuplo_variavel *array_var)
{
    if(a->dentro_array == dentro_array)
    {
        array elem = pop_array(a);
        converte_dados_var(elem);
        DADOS elem2 = convert_array_dados(elem);
        elem->elem_type = VARIAVEL;
        elem->elem_array.elem_variavel.indentificacao = c;
        elem->elem_array.elem_variavel.tipo = converte_tipo(elem->elem_type);
        push_array(a,elem);
        atualiza_array(array_var,c, elem2);
    }
    else
        associa_valor_array(a[a->size-1].elem_array.array_dentro,dentro_array,c,array_var);
}

/**
 * \brief função que adiciona o valor de uma variavel a um array.
 * @param a array no qual queremos adicionar a variavel.
 * @param dentro_array variavel que diz se estamos no array certo ou não.
 * @param c char que corresponde á variavel.
 * @param array_var array das variaveis atual.
 */
void push_variavel_array (array a, int dentro_array, char c, tuplo_variavel *array_var)
{
    if(a->dentro_array == dentro_array)
    {
        array elem = aloca_mem_array();
        elem->elem_type = converte_tipo_var(array_var[c-65]);
        switch (array_var[c-65].tipo)
        {
            case INTEIRO:
                elem->elem_array.elem_inteiro = array_var[c-65].tipo_variavel.variavel_int;
                break;
            case DOUBLE:
                elem->elem_array.elem_real = array_var[c-65].tipo_variavel.variavel_real;
                break;
            case TEXTO:
                strcpy(elem->elem_array.elem_string,array_var[c-65].tipo_variavel.variavel_string);
                break;
            case CARACTER:
                elem->elem_array.elem_char = array_var[c-65].tipo_variavel.variavel_char;
                break;
        }
        push_array(a,elem);
    }
    else
        push_variavel_array(a[a->size-1].elem_array.array_dentro,dentro_array,c,array_var);
}

/**
 * \brief função que decide aonda vamos dar push a uma variavel.
 * @param stack Stack atual.
 * @param N Endereço da stack atual.
 * @param c caracter que representa a variavel.
 * @param array_var Array com valores das variaveis.
 * @param dentro_array variavel que diz se estamos dentro de um array ou não.
 */
void add_var_value (DADOS *stack, int *N, char c, tuplo_variavel *array_var, int dentro_array)
{
    if (dentro_array == 0)
        push_variavel_omissao(stack,N, c,array_var);
    else
        push_variavel_array(stack[(*N)-1].dados.Array_stack,dentro_array,c,array_var);
}

/**
 * \brief função replica um elem da stack.
 * @param stack Stack atual.
 * @param N Endereço do comprimento da stack atual.
 */
void replica_elem (DADOS *stack, int *N)
{
    DADOS elem;
    elem = pop(stack, N);
    push(stack,N,stack[(*N)-elem.dados.numero_inteiro-1],stack[(*N)-elem.dados.numero_inteiro-1].type);
}
/**
 * \brief função que dependendo do token que recebe faz uma funçao logica diferente.
 * @param token a string
 * @param stack Stack atual.
 * @param N Endereço do comprimento da stack atual.
 * @param dentro_array variavel que diz o quão dentro estamos de um array.
 */
void nxttoken(char token[],DADOS *stack,int *N,int dentro_array){
    switch (token[1]) {
        case '<' :
            logica_menor(stack, N,dentro_array);
            break;
        case '>' :
            logica_maior(stack, N,dentro_array);
            break;
        case '|':
            logica_ou(stack, N, dentro_array);
            break;
        case '&':
            logica_e(stack, N, dentro_array);
            break;
    }
}
/**
 * \brief função que verifica se uma string é um número.
 * @param token string.
 * @return Elemento da stack com o respetivo tipo.
 */
DADOS verifica_numero (char *token)
{
    DADOS elem;
    char *sobra;
    elem.dados.numero_inteiro = strtol(token, &sobra, 10);
    if (strlen(sobra) == 0){
        elem.type = INT;
        return elem;
    }
    elem.dados.numero_real    = strtod(token, &sobra);
    if (strlen(sobra) == 0){
        elem.type = REAL;
        return elem;
    }
    else elem.type = STRING;
    return elem;
}

/**
 * \brief função que aloca memória.
 * @return array depois de termos memória para ele.
 */
array aloca_mem_array ()
{
    array a;
    a = malloc (20000 * sizeof (struct Struct_array));
    return a;
}

/**
 * \brief função que inicia um array dentro de outro array.
 * @param a array atual.
 * @param dentro_array qual é o nivel do array dentro do array.
 * @return array final.
 */
array inicia_array (array a, int dentro_array)
{
    a[a->size].elem_type = ARRAY;
    a[a->size].dentro_array = dentro_array;
    a[a->size].elem_array.array_dentro[0].dentro_array = dentro_array;
    a[a->size].elem_array.array_dentro[0].elem_type = ARRAY;
    a[a->size].elem_array.array_dentro[0].elem_array.elem_start_end = '[';
    a[a->size].elem_array.array_dentro[0].size = 1;
    return a;
}

/**
 * \brief função que junta um elemento a um array.
 * @param a array atual.
 * @param dentro_array o quão dentro do array estamos.
 * @param tipo_array Tipo que do elemento que queremos adicionar a um array.
 * @param token string que queremos adicionar.
 */
void push_elem_array (array a, int dentro_array, TIPO tipo_array, char *token)
{
    if (a->dentro_array == dentro_array)
    {
        char *sobra;
        a[a->size].dentro_array = dentro_array;
        a[a->size].elem_type    = tipo_array;
        switch (tipo_array) {
            case INT:
                a[a->size].elem_array.elem_inteiro = strtol(token, &sobra, 10);
                break;
            case REAL:
                a[a->size].elem_array.elem_real = strtod(token, &sobra);
                break;
            case CHAR:
                a[a->size].elem_array.elem_char = token[0];
                break;
            case VARIAVEL:
                break;
            case STRING:
                strcpy(a[a->size].elem_array.elem_string,token);
                break;
            case ARRAY:
                a[a->size].elem_array.elem_start_end = ']';
                break;
        }
        a->size++;
    }
    else if (a->dentro_array + 1 == dentro_array && token[0] == '[')
    {
        a[a->size].elem_array.array_dentro = aloca_mem_array();
        inicia_array(a, dentro_array);
        a->size++;
    }
    else
        push_elem_array(a[a->size-1].elem_array.array_dentro,dentro_array,tipo_array,token);

}

/**
 * \brief função que dá push a número dependendo se está dentro de um array ou não
 * @param stack Stack atual.
 * @param N Endereço da stack atual.
 * @param dentro_array variavel que diz quantas vezes estamos dentro de um array.
 * @param t Tipo do elemento dentro do array.
 * @param token String do elemento que queremos dar push.
 */
void push_numero (DADOS *stack, int *N, char *token, int dentro_array)
{
    if (dentro_array == 0)
        push(stack,N, verifica_numero(token), verifica_numero(token).type);
    else
        push_elem_array(stack[(*N)-1].dados.Array_stack,dentro_array, verifica_numero(token).type,token);
}

/**
 * \brief função que dá push a um char
 * @param stack Stack atual.
 * @param N endereço da stack atual.
 * @param token String que contem o char.
 * @param dentro_array variavel que diz quantas vezes estamos dentro de um array.
 */
void push_char (DADOS *stack,int *N, char *token, int dentro_array)
{
    DADOS elem;
    elem.dados.caracter = token[0];
    if (dentro_array == 0)
        push(stack,N,elem,CHAR);
    else
        push_elem_array(stack[(*N)-1].dados.Array_stack,dentro_array, CHAR,token);
}

/**
 * \brief função que dá push a uma string
 * @param stack Stack atual.
 * @param N endereço da stack atual.
 * @param token String que contem o char.
 * @param dentro_array variavel que diz quantas vezes estamos dentro de um array.
 */
void push_string (DADOS *stack,int *N, char *token, int dentro_array)
{
    DADOS elem;
    strcpy(elem.dados.string,token);
    if (dentro_array == 0)
        push(stack,N,elem,STRING);
    else
        push_elem_array(stack[(*N)-1].dados.Array_stack,dentro_array,STRING,token);
}
/**
 * \brief acrescenta um elemento no incio de um array.
 * @param a array que queremos adicionar o elemento.
 * @param elem elemento que queremos adicionar.
 */
void acrescenta_inicio (array a, array elem)
{
    int i;
    for (i = a->size; i > 1; i--)
        a[i] = a[i-1];
    a[1].elem_type = elem->elem_type;
    switch (elem->elem_type) {
        case INT:
            a[1].elem_array.elem_inteiro = elem->elem_array.elem_inteiro;
            break;
        case REAL:
            a[1].elem_array.elem_real = elem->elem_array.elem_real;
            break;
        case CHAR:
            a[1].elem_array.elem_char = elem->elem_array.elem_char;
            break;
        case VARIAVEL:
            a[1].elem_array.elem_variavel = elem->elem_array.elem_variavel;
            break;
        case ARRAY:
            a[1].elem_array.array_dentro = elem->elem_array.array_dentro;
            break;
        case STRING:
            strcpy(a[1].elem_array.elem_string,elem->elem_array.elem_string);
            break;
    }
    a->size++;
}
/**
 * \brief função que adiciona um elemento ao fim de um array mudando o tipo da respetiva posição para ARRAY.
 * @param a array atual.
 * @param elem elem que queremos adicionar.
 */
void muda_tipo (array a, array elem)
{
    a[a->size].dentro_array = elem->dentro_array;
    a[a->size].elem_type = ARRAY;
    a[a->size].elem_array.array_dentro = aloca_mem_array();
    a[a->size].elem_array.array_dentro = elem;
}

/**
 * \brief função que converte o valor de uma variavel sob a forma de real.
 * @param v Variavel que queremos converter.
 * @return Valor real.
 */
double double_var (tuplo_variavel v)
{
    double elem = 0;
    char *sobra;
    switch (v.tipo)
    {
        case INTEIRO:
            elem = v.tipo_variavel.variavel_int;
            break;
        case DOUBLE:
            elem = v.tipo_variavel.variavel_real;
            break;
        case CARACTER:
            elem = v.tipo_variavel.variavel_char;
            break;
        case TEXTO:
            elem = strtod(v.tipo_variavel.variavel_string, &sobra);
            break;
    }
    return  elem;
}

/**
 * \brief converte um elemento de um array para double.
 * @param a array atual.
 * @return valor da respetiva mudança.
 */
double dados_array (array a)
{
    double elem = 0;
    char *sobra;
    switch (a->elem_type)
    {
        case INT:
            elem = a->elem_array.elem_inteiro;
            break;
        case REAL:
            elem = a->elem_array.elem_real;
            break;
        case CHAR:
            elem = a->elem_array.elem_char;
            break;
        case STRING:
            if (*a->elem_array.elem_string == '"')
            {
                move_pointer(a->elem_array.elem_string);
                a->elem_array.elem_string[strlen(a->elem_array.elem_string)] = '\0';
            }
            elem = strtod(a->elem_array.elem_string, &sobra);
            break;
        case VARIAVEL:
            elem = double_var(a->elem_array.elem_variavel);
            break;
        case ARRAY:
            break;
    }
    return elem;
}
/**
 * \brief função que adiciona o resultado de uma operação aritmética para um array.
 * @param a_push array que queremos adicionar o elemento.
 * @param res resultado da operação artimética.
 */
void array_double (array a_push,double res)
{
    if (res == floor(res))
    {
        a_push[a_push->size].elem_type = INT;
        a_push[a_push->size].elem_array.elem_inteiro = res;
    }
    else
    {
        a_push[a_push->size].elem_type = REAL;
        a_push[a_push->size].elem_array.elem_real = res;
    }
    a_push->size++;
}
/**
 * \brief concatena dois array.
 * @param a array que queremos adicionar elementos.
 * @param b array que vamos buscar os elementos a adicionar.
 * @return array depois da concatenação.
 */
array concat_array (array a, array b)
{
    int i, j = 1;
    a->size -= 1;
    for (i = a->size; j < b->size; i++)
    {
        a[i] = b[j];
        j++;
        a->size++;
    }
    return a;
}

/**
 * \brief função que move o pointer uma casa para a frente.
 * @param s string que queremos realizar a operação.
 */
void move_pointer_frente (char *s)
{
    int i;
    for(i = strlen(s); i > 0; i--)
    {
        s[i] = s[i-1];
    }
}

/**
 * \brief converte um tipo de dados da stack para um tipo de um elemento do array.
 * @param d Dados que queremos converter.
 * @return resultado da conversao.
 */
array dados_para_array (DADOS d)
{
    array a = aloca_mem_array();
    a->elem_type = d.type;
    switch (d.type)
    {
        case INT:
            a->elem_array.elem_inteiro = d.dados.numero_inteiro;
            break;
        case REAL:
            a->elem_array.elem_real = d.dados.numero_real;
            break;
        case CHAR:
            a->elem_array.elem_char = d.dados.caracter;
            break;
        case STRING:
            strcpy(a->elem_array.elem_string,d.dados.string);
            break;
        case VARIAVEL:
            a->elem_array.elem_variavel = d.dados.variavel;
            break;
        case ARRAY:
            break;
    }
    return a;
}

/**
 * \brief funçao que concatena duas string.
 * @param a array aonde colocamos a string da concatenaçao.
 * @param a1 array 1.
 * @param a2 array 2.
 */
void concats_strings (array a, array a1, array a2)
{
    if (a1->elem_type == STRING && a2->elem_type == STRING)
    {
        a2->elem_array.elem_string[strlen(a2->elem_array.elem_string)-1] = '\0';
        move_pointer(a1->elem_array.elem_string);
        strcat(a2->elem_array.elem_string,a1->elem_array.elem_string);
        push_array(a,a2);
    }
    else if(a1->elem_type == CHAR && a2->elem_type == STRING)
    {
        a2->elem_array.elem_string[strlen(a2->elem_array.elem_string)] = '"';
        a2->elem_array.elem_string[strlen(a2->elem_array.elem_string)-2] = a1->elem_array.elem_char;
        push_array(a,a2);
    }
    else if(a1->elem_type == STRING && a2->elem_type == CHAR)
    {
        move_pointer_frente(a1->elem_array.elem_string);
        a1->elem_array.elem_string[1] = a2->elem_array.elem_char;
        push_array(a,a1);
    }
}

/**
 * \brief funçao que concatena dois arrays.
 * @param a array aonde colocamos o array da concatenaçao.
 * @param a1 array 1.
 * @param a2 array 2.
 */
void concat_arrays (array a, array a1, array a2)
{
    if (a1->elem_type == ARRAY && a2->elem_type == ARRAY)
    {
        concat_array(a2,a1);
        push_array(a,a2);
    }
    else if (a2->elem_type == ARRAY)
    {
        push_array(a2,a1);
        push_array(a,a2);
    }
    else if (a1->elem_type == ARRAY)
    {
        acrescenta_inicio(a1,a2);
        push_array(a,a1);
    }
}

/**
 * \brief funçao que soma dois arrays.
 * @param a array aonde colocamos o array da soma.
 * @param a1 array 1.
 * @param a2 array 2.
 */
void soma_array (array a, array a1, array a2)
{
    double x = dados_array(a1);
    double y = dados_array(a2);
    array_double(a,x+y);
}

/**
 * \brief função que decide qual operação a fazer dependendo dos tipos do array.
 * @param a array que queremos realizar a operaçao.
 * @param dentro_array variavel que diz o quao dentro esta o array.
 */
void operador_mais_array (array a,int dentro_array)
{
    if (a->dentro_array == dentro_array)
    {
        array a1 = pop_array(a);
        array a2 = pop_array(a);
        if (a2->elem_type == ARRAY || a1->elem_type == ARRAY)
            concat_arrays(a,a1,a2);
        else if (a2->elem_type == STRING || a1->elem_type == STRING)
            concats_strings(a,a1,a2);
        else
            soma_array(a,a1,a2);
    }
    else
        operador_mais_array(a[a->size-1].elem_array.array_dentro,dentro_array);
}

/**
 * \brief converte um elemento da stack para string.
 * @param d elemento que queremos converter.
 * @param l string aonde colocamos o resultado.
 * @return string depois da conversão.
 */
char *convert_string (DADOS d, char *l)
{
    switch (d.type)
    {
        case INT:
            sprintf(l,"%ld",d.dados.numero_inteiro);
            break;
        case REAL:
            sprintf(l,"%.6g",d.dados.numero_real);
            break;
        case CHAR:
            sprintf(l,"%c",d.dados.caracter);
            break;
        case VARIAVEL:
            break;
        case STRING:
            break;
        case ARRAY:
            break;
    }
    move_pointer_frente(l);
    l[0] = '"';
    l[strlen(l)] = '"';
    return l;
}

/**
 * \brief função que concatena duas string e coloca na stack.
 * @param stack Stack atual.
 * @param N Endereço do comprimento da stack atual.
 */
void concat_string_stack (DADOS *stack, int *N)
{
    DADOS d1 = pop(stack,N);
    DADOS d2 = pop(stack,N);
    if (d1.type != STRING)
        convert_string(d1,d1.dados.string);
    if (d2.type != STRING)
        convert_string(d2,d2.dados.string);
    move_pointer(d1.dados.string);
    d2.dados.string[strlen(d2.dados.string)-1] = '\0';
    strcat(d2.dados.string,d1.dados.string);
    push(stack,N,d2,STRING);
}

/**
 * \brief função que concatena dois arrays e coloca na stack.
 * @param stack stack atual.
 * @param N Endereço da stack atual.
 */
void concat_array_stack (DADOS *stack, int *N)
{
    DADOS d1 = pop(stack,N);
    DADOS d2 = pop(stack,N);
    if (d1.type == ARRAY && d2.type == ARRAY)
    {
        concat_array(d2.dados.Array_stack,d1.dados.Array_stack);
        push(stack,N,d2,ARRAY);
    }
    else if (d1.type == ARRAY)
    {
        array p = dados_para_array(d2);
        acrescenta_inicio(d1.dados.Array_stack,p);
        push(stack,N,d1,ARRAY);
    }
    else if (d2.type == ARRAY)
    {
        array p = dados_para_array(d1);
        push_array(d2.dados.Array_stack,p);
        push(stack,N,d2,ARRAY);
    }
}

/**
 * \brief funçao que decide qual sera a operaçao quando se le o token '+'
 * @param stack stack atual.
 * @param N Endereço da stack atual.
 * @param dentro_array variavel que diz o quao dentro esta o array.
 */
void operador_mais (DADOS *stack, int *N, int dentro_array)
{
    if ((stack[(*N)-1].type == ARRAY || stack[(*N)-2].type == ARRAY) && dentro_array == 0)
        concat_array_stack(stack,N);
    else if ((stack[(*N)-1].type == STRING || stack[(*N)-2].type == STRING) && dentro_array == 0)
        concat_string_stack(stack,N);
    else if (dentro_array == 0)
        soma(stack,N);
    else
        operador_mais_array (stack[(*N)-1].dados.Array_stack,dentro_array);
}
/**
 * \brief funçao que vai buscar o array e aplica a operação '^' ao ultimo e penultimo elemento.
 * só funciona para inteiros.
 * @param a array atual.
 * @param dentro_array variavel que diz em que grau esta o array.
 */
void operador_xor_array (array a, int dentro_array)
{
    if (a->dentro_array == dentro_array)
    {
        array a1 = pop_array(a);
        array a2 = pop_array(a);
        a1->elem_array.elem_inteiro = a2->elem_array.elem_inteiro;
        push_array(a,a1);
    } else
        operador_xor_array(a[a->size-1].elem_array.array_dentro,dentro_array);
}
/**
 * \brief funçao que decide qual operaçao vai realizar quando le o char '^'.
 * @param stack stack atual.
 * @param N Endereço da stack atual.
 * @param dentro_array variavel que diz em que grau estamos em termos de array's.
 */
void operador_xor (DADOS *stack, int *N, int dentro_array)
{
    if (dentro_array == 0)
        xor(stack,N);
    else
        operador_xor_array(stack[(*N)-1].dados.Array_stack,dentro_array);

}
/**
 * \brief funçao que vai buscar o array e aplica a operação '|' ao ultimo e penultimo elemento.
 * só funciona para inteiros.
 * @param a array atual.
 * @param dentro_array variavel que diz em que grau esta o array.
 */
void operador_or_array (array a, int dentro_array)
{
    if (a->dentro_array == dentro_array)
    {
        array a1 = pop_array(a);
        array a2 = pop_array(a);
        a1->elem_array.elem_inteiro |= a2->elem_array.elem_inteiro;
        push_array(a,a1);
    } else
        operador_or_array(a[a->size-1].elem_array.array_dentro,dentro_array);
}
/**
 * \brief funçao que decide qual operaçao vai realizar quando le o char '|'.
 * @param stack stack atual.
 * @param N Endereço da stack atual.
 * @param dentro_array variavel que diz em que grau estamos em termos de array's.
 */
void operador_or (DADOS *stack, int *N, int dentro_array)
{
    if (dentro_array == 0)
        or(stack,N);
    else
        operador_or_array(stack[(*N)-1].dados.Array_stack,dentro_array);

}
/**
 * \brief funçao que decide qual operaçao vai realizar quando le o char '&'.
 * @param stack stack atual.
 * @param N Endereço da stack atual.
 * @param dentro_array variavel que diz em que grau estamos em termos de array's.
 */
void operador_e_array (array a, int dentro_array)
{
    if (a->dentro_array == dentro_array)
    {
        array a1 = pop_array(a);
        array a2 = pop_array(a);
        a1->elem_array.elem_inteiro &= a2->elem_array.elem_inteiro;
        push_array(a,a1);
    } else
        operador_e_array(a[a->size-1].elem_array.array_dentro,dentro_array);
}
/**
 * \brief funçao que decide qual operaçao vai realizar quando le o char '&'.
 * @param stack stack atual.
 * @param N Endereço da stack atual.
 * @param dentro_array variavel que diz em que grau estamos em termos de array's.
 */
void operador_e (DADOS *stack, int *N, int dentro_array)
{
    if (dentro_array == 0)
        and(stack,N);
    else
        operador_e_array(stack[(*N)-1].dados.Array_stack,dentro_array);

}
/**
 * \brief funçao que vai buscar o array e muda o valor lógico do ultimo elemento.
 * @param a array atual.
 * @param dentro_array variavel que diz em que grau esta o array.
 */
void change_bool_array (array a, int dentro_array)
{
    if(a->dentro_array == dentro_array)
    {
        array a1 = pop_array(a);
        a1->elem_array.elem_inteiro = dados_array(a1) == 0;
        a1->elem_type = INT;
        push_array(a,a1);
    }
    else
        change_bool_array(a[a->size-1].elem_array.array_dentro,dentro_array);
}
/**
 * \brief funçao que decide qual operaçao vai realizar quando le o char '!'.
 * @param stack stack atual.
 * @param N Endereço da stack atual.
 * @param dentro_array variavel que diz em que grau estamos em termos de array's.
 */
void operador_exclamacao (DADOS *stack, int *N, int dentro_array)
{
    if(dentro_array == 0)
        change_bool(stack,N);
    else
        change_bool_array(stack[(*N)-1].dados.Array_stack,dentro_array);
}
/**
 * \brief funçao que procura uma string e devolve o indice onde s2 ocorre em s1. Caso nao encontre devolde -1.
 * @param s1 string principal.
 * @param s2 string que ocorre ou nao em s1.
 */
int procura_string (char *s1, char *s2)
{
    s1[strlen(s1)-1] = '\0';
    s2[strlen(s2)-1] = '\0';
    int i, j = 1, pos = -1;
    for (i = 1; s1[i] != '\0' && s2[j] != '\0'; i++)
    {
        if (s1[i] == s2[j])
        {
            if(pos == -1) pos = i-1;
            j++;
        }
        else
        {
            pos = -1;
            j = 1;
        }
    }
    if(s2[j] == '\0') return  pos;
    else return -1;
}
/**
 * \brief funçao que vai buscar o array e procurar a substring na string e devolve o índice ou -1 se não encontrar.
 * @param a array atual.
 * @param dentro_array variavel que diz em que grau esta o array.
 */
void hastag_array (array a, int dentro_array)
{
    if(a->dentro_array == dentro_array)
    {
        array a1 = pop_array(a);
        array a2 = pop_array(a);
        if(a1->elem_type == STRING && a2->elem_type == STRING)
        {
            a1->elem_array.elem_inteiro = procura_string(a2->elem_array.elem_string,a1->elem_array.elem_string);
            a1->elem_type = INT;
            push_array(a,a1);
        }
        else
        {
            double x = dados_array(a1);
            double y = dados_array(a2);
            array_double(a, pow(y,x));
        }
    }
    else
        hastag_array(a[a->size-1].elem_array.array_dentro,dentro_array);
}
/**
 * \brief funçao que decide qual operaçao vai realizar quando le o char '#'.
 * @param stack stack atual.
 * @param N Endereço da stack atual.
 * @param dentro_array variavel que diz em que grau estamos em termos de array's.
 */
void hashtag (DADOS *stack, int *N, int dentro_array)
{
    if (dentro_array == 0)
    {
        if(stack[(*N)-1].type == STRING && stack[(*N)-2].type == STRING)
        {
            DADOS d1 = pop(stack,N);
            DADOS d2 = pop(stack,N);
            d1.dados.numero_inteiro = procura_string(d2.dados.string,d1.dados.string);
            push(stack,N,d1,INT);
        }
        else
            expoente(stack,N);
    }
    else
        hastag_array(stack[(*N)-1].dados.Array_stack,dentro_array);
}
/**
 * \brief funçao que lê o input.
 * @param stack stack atual.
 * @param N Endereço da stack atual.
 * @param dentro_array variavel que diz em que grau estamos em termos de array's.
 */
void ler_input(DADOS *stack, int *N, int dentro_array)
{
    char *input;
    char con[1000];
    input = malloc (sizeof (con));
    int k = 0;
    con[0] = '"';
    while(strlen(con) <= 1000 && k == 0)
    {
        input = fgets (input, 1000,stdin);
        if (input == NULL) k = 1;
        else strcat(con,input);
    }
    con[strlen(con)] = '"';
    push_string(stack,N,con,dentro_array);
}
/**
 * \brief funçao que decide qual operaçao vai realizar quando le o char '<'.
 * @param stack stack atual.
 * @param N Endereço da stack atual.
 * @param dentro_array variavel que diz em que grau estamos em termos de array's.
 */
void operador_menor (DADOS *stack, int *N, int dentro_array)
{
    if (stack[(*N)-2].type == STRING && stack[(*N)-1].type == STRING)
    {
        DADOS d1 = pop(stack,N);
        DADOS d2 = pop(stack,N);
        d1.dados.numero_inteiro = minor_strings(d2.dados.string,d1.dados.string);
        push(stack,N,d1,INT);
    }
    else if (stack[(*N)-2].type != ARRAY && dentro_array == 0)
        minor(stack,N);
    else if (stack[(*N)-2].type == ARRAY && dentro_array == 0)
    {
        DADOS d1 = pop(stack,N);
        DADOS d2 = pop(stack,N);
        int pos = d1.dados.numero_inteiro;
        d2.dados.Array_stack->size = pos + 1;
        d2.dados.Array_stack[d2.dados.Array_stack->size].elem_type = ARRAY;
        d2.dados.Array_stack[d2.dados.Array_stack->size].elem_array.elem_start_end = ']';
        d2.dados.Array_stack->size++;
        push(stack,N,d2,ARRAY);
    }
    else
        operador_minor_array(stack[(*N)-1].dados.Array_stack,dentro_array);
}
/**
 * \brief funçao que vai buscar o array para que possa ir buscar X elementos ao mesmo.
 * @param a array atual.
 * @param dentro_array variavel que diz em que grau esta o array.
 */
void operador_minor_array (array a, int dentro_array)
{
    if(a->dentro_array == dentro_array)
    {
        if (a[a->size-1].elem_type == STRING && a[a->size-2].elem_type == STRING)
        {
            array a1,a2;
            a1 = pop_array(a);
            a2 = pop_array(a);
            array elem = aloca_mem_array();
            elem->elem_array.elem_inteiro = minor_strings(a2->elem_array.elem_string,a1->elem_array.elem_string);
            elem->elem_type = INT;
            push_array(a,elem);
        }
        else if (a[a->size-1].dentro_array == dentro_array && a[a->size-2].dentro_array == dentro_array)
        {
            array a1,a2;
            a1 = pop_array(a);
            a2 = pop_array(a);
            double x = dados_array(a1);
            double y = dados_array(a2);
            array_double(a,y<x);
        }
        else
        {
            int pos = pop_array(a)->elem_array.elem_inteiro;
            array b = pop_array(a);
            b->size = pos + 1;
            b[b->size].elem_type = ARRAY;
            b[b->size].elem_array.elem_start_end = ']';
            b->size++;
            push_array(a,b);
        }
    }
    else
        operador_minor_array(a[a->size-1].elem_array.array_dentro,dentro_array);
}
/**
 * \brief funçao que vai buscar o array e calcula o resto da divisão entre o ultimo e penultimo elemento.
 * só funciona para inteiros.
 * @param a array atual.
 * @param dentro_array variavel que diz em que grau esta o array.
 */
void operador_resto_array (array a, int dentro_array)
{
    if(a->dentro_array == dentro_array)
    {
        array a1 = pop_array(a);
        array a2 = pop_array(a);
        a2->elem_array.elem_inteiro %= a1->elem_array.elem_inteiro;
        push_array(a,a2);
    }
    else
        operador_resto_array(a[a->size-1].elem_array.array_dentro,dentro_array);
}
/**
 * \brief funçao que vai buscar o array e subtrai os dois últimos elementos.
 * @param a array atual.
 * @param dentro_array variavel que diz em que grau esta o array.
 */
void operador_menos_array (array a, int dentro_array)
{
    if(a->dentro_array == dentro_array)
    {
        array a1 = pop_array(a);
        array a2 = pop_array(a);
        double x = dados_array(a1);
        double y = dados_array(a2);
        array_double(a,y-x);
    }
    else
        operador_menos_array(a[a->size-1].elem_array.array_dentro,dentro_array);
}
/**
 * \brief funçao que decide qual operaçao vai realizar quando le o char '%'.
 * @param stack stack atual.
 * @param N Endereço da stack atual.
 * @param dentro_array variavel que diz em que grau estamos em termos de array's.
 */
void operador_resto (DADOS *stack, int *N, int dentro_array)
{
    if(dentro_array == 0)
        resto(stack,N);
    else
        operador_resto_array(stack[(*N)-1].dados.Array_stack,dentro_array);
}

/**
 * \brief funçao que decide qual operaçao vai realizar quando le o char '-'.
 * @param stack stack atual.
 * @param N Endereço da stack atual.
 * @param dentro_array variavel que diz em que grau estamos em termos de array's.
 */
void operador_menos (DADOS *stack, int *N, int dentro_array)
{
    if(dentro_array == 0)
        subtracao(stack,N);
    else
        operador_menos_array(stack[(*N)-1].dados.Array_stack,dentro_array);
}

/**
 * \brief função que multiplica um dado array.
 * @param a array que queremos multiplicar.
 * @param vezes número de vezes que queremos multiplicar.
 * @return array multiplicado n vezes.
 */
array multiplica_array (array a, int vezes)
{
    int i;
    int j = a->size - 1;
    int s = ((a->size) - 2) * vezes + 1;
    for (i = 1; i < s; i++)
    {
        a[j] = a[i];
        j++;
    }
    a[i].elem_array.elem_start_end = ']';
    a[i].elem_type = ARRAY;
    a[i].dentro_array = a->dentro_array;
    a->size = i + 1;
    return a;
}
/**
 * \brief função que multiplica uma string n vezes.
 * @param s string que queremos multiplicar.
 * @param vezes numero de vezes.
 * @return string final.
 */
char *multiplica_string (char *s, int vezes)
{
    s[strlen(s)-1] = '\0';
    int i;
    int j = 1;
    int size = strlen(s);
    for (i = size; i < (size-1) * vezes + 1;i++)
    {
        s[i] = s[j];
        j++;
    }
    s[i] = '"';
    return s;
}
/**
 * \brief funçao que vai buscar o array que queremos multiplicar.
 * @param a array atual.
 * @param dentro_array variavel que diz em que grau esta o array.
 */
void operador_vezes_array (array a,int dentro_array)
{
    if (a->dentro_array == dentro_array)
    {
        array a1 = pop_array(a);
        array a2 = pop_array(a);
        if(a2->elem_type == STRING)
        {
            multiplica_string(a2->elem_array.elem_string,a1->elem_array.elem_inteiro);
            push_array(a,a2);
        }
        else if (a2->elem_type != ARRAY)
        {
            double x = dados_array(a1);
            double y = dados_array(a2);
            array_double(a,x*y);
        }
        else
        {
            int vezes = a1->elem_array.elem_inteiro;
            multiplica_array(a2,vezes);
            push_array(a,a2);
        }
    }
    else
        operador_vezes_array(a[a->size-1].elem_array.array_dentro,dentro_array);
}
/**
 * \brief funçao que decide qual operaçao vai realizar quando le o char '*'.
 * @param stack stack atual.
 * @param N Endereço da stack atual.
 * @param dentro_array variavel que diz em que grau estamos em termos de array's.
 */
void operador_vezes (DADOS *stack, int *N, int dentro_array)
{
    if (stack[(*N)-1].type != ARRAY && stack[(*N)-2].type != ARRAY && stack[(*N)-1].type != STRING && stack[(*N)-2].type != STRING)
        multiplicacao(stack,N);
    else if (dentro_array==0)
    {
        DADOS d1 = pop(stack,N);
        int vezes = d1.dados.numero_inteiro;
        if (stack[(*N)-1].type == ARRAY)
            multiplica_array(stack[(*N)-1].dados.Array_stack, vezes);
        else
        {
            DADOS d2= pop(stack,N);
            multiplica_string(d2.dados.string,vezes);
            push(stack,N,d2,STRING);
        }
    }
    else
        operador_vezes_array (stack[(*N)-1].dados.Array_stack,dentro_array);
}

/**
 * \brief função que vai buscar o n elemento de um array que está na ultima posição.
 * @param a array que está o array que queremos ir buscar o n elemento.
 */
void get_n_elem_array_array (array a)
{
    int pos = pop_array(a)->elem_array.elem_inteiro;
    array b = pop_array(a);
    a[a->size].elem_type = b[pos+1].elem_type;
    a[a->size] = b[pos+1];
    a[a->size].dentro_array--;
    a->size++;
}
/**
 * \brief função que vai buscar o n elemento de uma string que está na ultima posição.
 * @param a array que está a string que queremos ir buscar o n elemento.
 */
void get_n_elem_string_array (array a)
{
    array a1 = pop_array(a);
    array a2 = pop_array(a);
    array a3 = aloca_mem_array();
    a3->elem_array.elem_char = a2->elem_array.elem_string[a1->elem_array.elem_inteiro-1];
    a3->elem_type = CHAR;
    push_array(a,a3);
}

/**
 * \brief função que compara duas string que estão dentro de um array.
 * @param a array que contem as 2 strings.
 */
void cmp_string_array (array a)
{
    array a1 = pop_array(a);
    array a2 = pop_array(a);
    array elem = aloca_mem_array();
    elem->elem_type = INT;
    elem->elem_array.elem_inteiro = 0;
    if(strcmp(a1->elem_array.elem_string,a2->elem_array.elem_string) == 0)elem->elem_array.elem_inteiro = 1;
    push_array(a,elem);
}

/**
 * \brief função que vê se os 2 elementos do topo do array são iguais.
 * @param a array que estamos a operar.
 */
void array_equal (array a)
{
    array a1,a2;
    a1 = pop_array(a);
    a2 = pop_array(a);
    double x = dados_array(a1);
    double y = dados_array(a2);
    array_double(a,y==x);
}

/**
 * \brief funçao que vai buscar o array para que possa ir buscar um valor por indice ao mesmo.
 * @param a array atual.
 * @param dentro_array variavel que diz em que grau esta o array.
 */
void operador_igual_array (array a, int dentro_array)
{
    if(a->dentro_array == dentro_array)
    {
        if (a[a->size-1].elem_type == INT && a[a->size-2].elem_type == STRING)
            get_n_elem_string_array(a);
        else if (a[a->size-1].elem_type == STRING && a[a->size-2].elem_type == STRING)
            cmp_string_array(a);
        else if (a[a->size-1].dentro_array == dentro_array && a[a->size-2].dentro_array ==dentro_array)
            array_equal(a);
        else
            get_n_elem_array_array(a);
    }
    else
        operador_igual_array(a[a->size-1].elem_array.array_dentro,dentro_array);
}

/**
 * \brief função que vai buscar o n elemento de um array e coloca na stack
 * @param stack stack atual.
 * @param N endereço do comprimento da stack atual.
 */
void get_elem_n_array (DADOS *stack, int *N)
{
    DADOS d1 = pop(stack,N);
    DADOS d2 = pop(stack,N);
    DADOS d3 = convert_array_dados(d2.dados.Array_stack + d1.dados.numero_inteiro + 1);
    push(stack,N,d3,d3.type);
}

/**
 * \brief função que vai buscar o n elemento de uma string e coloca na stack.
 * @param stack stack atual.
 * @param N endereço do comprimento da stack atual.
 */
void get_elem_n_string (DADOS *stack, int *N)
{
    DADOS d1 = pop(stack,N);
    DADOS d2 = pop(stack,N);
    DADOS d3;
    d3.type = CHAR;
    d3.dados.caracter = d2.dados.string[d1.dados.numero_inteiro+1];
    push(stack,N,d3,CHAR);
}

/**
 * \brief função que compara 2 strings que estão no topo da stack e coloca na stack o resultado.
 * @param stack stack atual
 * @param N endereço do comprimento da stack atual.
 */
void cmp_string_stack (DADOS *stack, int *N)
{
    DADOS d1 = pop(stack,N);
    DADOS d2 = pop(stack,N);
    DADOS d3;
    d3.dados.numero_inteiro = 0;
    if(strcmp(d1.dados.string,d2.dados.string) == 0) d3.dados.numero_inteiro = 1;
    push(stack,N,d3,INT);
}

/**
 * \brief função que vai buscar o n elemento de uma string que está numa variavel e coloca na stack.
 * @param stack stack atual
 * @param N endereço do comprimento da stack atual.
 */
void get_elem_n_var (DADOS *stack, int *N)
{
    DADOS d1 = pop(stack,N);
    DADOS d2 = pop(stack,N);
    DADOS d3;
    d3.dados.caracter = d2.dados.variavel.tipo_variavel.variavel_string[d1.dados.numero_inteiro + 1];
    d3.type = CHAR;
    push(stack,N,d3,CHAR);
}

/**
 * \brief funçao que decide qual operaçao vai realizar quando le o char '='.
 * @param stack stack atual.
 * @param N Endereço da stack atual.
 * @param dentro_array variavel que diz em que grau estamos em termos de array's.
 */
void operador_igual (DADOS *stack,int *N, int dentro_array)
{
    if (dentro_array == 0)
    {
        if (stack[(*N)-2].type != ARRAY && stack[(*N)-2].type != STRING && stack[(*N)-2].type != VARIAVEL)
            equal(stack,N);
        else if (stack[(*N)-2].type == STRING && stack[(*N)-1].type != STRING)
            get_elem_n_string(stack,N);
        else if (stack[(*N)-2].type == ARRAY)
            get_elem_n_array(stack,N);
        else if (stack[(*N)-2].type == STRING && stack[(*N)-1].type == STRING)
            cmp_string_stack(stack,N);
        else if (stack[(*N)-2].type == VARIAVEL)
            get_elem_n_var(stack,N);
    }
    else
        operador_igual_array(stack[(*N)-1].dados.Array_stack,dentro_array);
}


/**
 * \brief funçao que vai buscar o array para que possa ir buscar X elementos ao mesmo.
 * @param a array atual.
 * @param dentro_array variavel que diz em que grau esta o array.
 */
void operador_bigger_array (array a, int dentro_array)
{
    if(a->dentro_array == dentro_array)
    {
        if (a[a->size-1].elem_type == STRING && a[a->size-2].elem_type == STRING)
        {
            array a1,a2;
            a1 = pop_array(a);
            a2 = pop_array(a);
            array elem = aloca_mem_array();
            elem->elem_array.elem_inteiro = bigger_strings(a2->elem_array.elem_string,a1->elem_array.elem_string);
            elem->elem_type = INT;
            push_array(a,elem);
        }
        if (a[a->size-1].dentro_array == dentro_array && a[a->size-2].dentro_array == dentro_array)
        {
            array a1,a2;
            a1 = pop_array(a);
            a2 = pop_array(a);
            double x = dados_array(a1);
            double y = dados_array(a2);
            array_double(a,y>x);
        }
        else
        {
            int pos = pop_array(a)->elem_array.elem_inteiro;
            array b = pop_array(a);
            int p = b->size - 1 - pos;
            b[p-1].elem_type = ARRAY;
            b[p-1].elem_array.elem_start_end = '[';
            b[p-1].dentro_array = b->dentro_array;
            b+= p - 1;
            b->size = pos + 2;
            push_array(a,b);
        }
    }
    else
        operador_bigger_array(a[a->size-1].elem_array.array_dentro,dentro_array);
}

/**
 * \brief funçao que decide qual operaçao vai realizar quando le o char '>'.
 * @param stack stack atual.
 * @param N Endereço da stack atual.
 * @param dentro_array variavel que diz em que grau estamos em termos de array's.
 */
void operador_bigger (DADOS *stack, int *N, int dentro_array)
{
    if (stack[(*N)-2].type == STRING && stack[(*N)-1].type == STRING)
    {
        DADOS d1 = pop(stack,N);
        DADOS d2 = pop(stack,N);
        d1.dados.numero_inteiro = bigger_strings(d2.dados.string,d1.dados.string);
        push(stack,N,d1,INT);
    }
    else if (stack[(*N)-2].type != ARRAY && dentro_array == 0)
        bigger(stack,N);
    else if (stack[(*N)-2].type == ARRAY && dentro_array == 0)
    {
        DADOS d1 = pop(stack,N);
        DADOS d2 = pop(stack,N);
        int pos = d1.dados.numero_inteiro;
        int p = d2.dados.Array_stack->size - 1 - pos;
        d2.dados.Array_stack[p-1].elem_type = ARRAY;
        d2.dados.Array_stack[p-1].elem_array.elem_start_end = '[';
        d2.dados.Array_stack[p-1].dentro_array = d2.dados.Array_stack->dentro_array;
        d2.dados.Array_stack+= p - 1;
        d2.dados.Array_stack->size = pos + 2;
        push(stack,N,d2,ARRAY);
    }
    else
        operador_bigger_array(stack[(*N)-1].dados.Array_stack,dentro_array);
}

/**
 * \brief funçao que vai buscar o array e muda o seu último valor lógico.
 * @param a array atual.
 * @param dentro_array variavel que diz em que grau esta o array.
 */
void operador_inte_array (array a, int dentro_array)
{
    if(a->dentro_array == dentro_array)
    {
        array a1,a2,a3;
        a1=pop_array(a);
        a2=pop_array(a);
        a3=pop_array(a);
        if (dados_array(a3) != 0)
            push_array(a, a2);
        else
            push_array(a,a1);
    }
    else
        operador_inte_array(a[a->size-1].elem_array.array_dentro,dentro_array);
}


/**
 * \brief funçao que decide qual operaçao vai realizar quando le o char '?'.
 * @param stack stack atual.
 * @param N Endereço da stack atual.
 * @param dentro_array variavel que diz em que grau estamos em termos de array's.
 */
void operador_interrogacao (DADOS *stack, int *N, int dentro_array)
{
    if(dentro_array == 0)
        if_then_else(stack,N);
    else
        operador_inte_array(stack[(*N)-1].dados.Array_stack,dentro_array);
}

/**
 * \brief função que calcula o tamanho ou range de um dado array.
 * @param elem array cujo tamanho vamos calcular.
 * @param size tamanho do array.
 * @param dentro_array variavel que diz em que grau esta o array.
 */
void range (array elem, int size,int dentro_array)
{
    int i;
    for (i = 1; i < size+1; i++)
    {
        elem[i].elem_array.elem_inteiro = i-1;
        elem[i].elem_type = INT;
        elem[i].dentro_array = dentro_array;
    }
    elem[i].elem_array.elem_start_end = ']';
    elem[i].dentro_array = dentro_array;
    elem[i].elem_type = ARRAY;
    elem->size = i + 1;
}

/**
 * \brief funçao que vai buscar o array para que possa ser calculado o seu tamanho ou range.
 * @param a array atual.
 * @param dentro_array variavel que diz em que grau esta o array.
 */
void tamanho_range_array (array a, int dentro_array)
{
    if (a->dentro_array == dentro_array)
    {
        if (a[a->size-1].elem_type == STRING)
        {
            array a1 = pop_array(a);
            a1->elem_array.elem_inteiro = strlen(a1->elem_array.elem_string) - 2;
            a1->elem_type = INT;
            push_array(a,a1);
        }
        else if (a[a->size-1].elem_type == ARRAY)
        {
            a[a->size-1].elem_type = INT;
            a[a->size-1].elem_array.elem_inteiro = a[a->size-1].elem_array.array_dentro->size - 2;
        }
        else
        {
            int size = pop_array(a)->elem_array.elem_inteiro;
            a[a->size].elem_array.array_dentro = aloca_mem_array();
            inicia_array(a,dentro_array+1);
            array elem = a[a->size].elem_array.array_dentro;
            range(elem,size,dentro_array + 1);
            push_array(a,elem);
        }
    }
    else
        tamanho_range_array(a[a->size-1].elem_array.array_dentro,dentro_array);
}

/**
 * \brief funçao que decide qual operaçao vai realizar quando le o char ','.
 * @param stack stack atual.
 * @param N Endereço da stack atual.
 * @param dentro_array variavel que diz em que grau estamos em termos de array's.
 */
void tamanho_range (DADOS *stack, int *N, int dentro_array)
{
    if (stack[(*N)-1].type == ARRAY && dentro_array == 0)
    {
        DADOS d = pop(stack,N);
        d.dados.numero_inteiro = d.dados.Array_stack->size - 2;
        push(stack,N,d,INT);
    }
    else if (stack[(*N)-1].type == STRING && dentro_array == 0)
    {
        DADOS d = pop(stack,N);
        d.dados.numero_inteiro = strlen(d.dados.string) - 2;
        push(stack,N,d,INT);
    }
    else if (stack[(*N)-1].type != ARRAY && dentro_array == 0)
    {
        DADOS d;
        int size = pop(stack,N).dados.numero_inteiro;
        d.dados.Array_stack = aloca_mem_array();
        d.dados.Array_stack[0].size = 1;
        d.dados.Array_stack[0].elem_type = ARRAY;
        d.dados.Array_stack[0].elem_array.elem_start_end = '[';
        d.dados.Array_stack[0].dentro_array = 1;
        range(d.dados.Array_stack,size,dentro_array);
        push(stack,N,d,ARRAY);
    }
    else tamanho_range_array(stack[(*N)-1].dados.Array_stack,dentro_array);
}

/**
 * \brief função que diminui uma unidade o apontador para dentro_array
 * @param a array que queremos realizar  a operação.
 */
void reduz_dentro_array (array a)
{
    int i;
    for(i = 0; i < a->size; i++)
    {
        if(a[i].elem_type == ARRAY && a[i].elem_array.elem_start_end != '['&& a[i].elem_array.elem_start_end != ']')
            reduz_dentro_array(a[i].elem_array.array_dentro);
        else a[i].dentro_array--;
    }
}

/**
 * \brief função que transfere dados de um elemento de um array para outro.
 * @param a array que queremos replicar.
 * @return array replicado.
 */
array transfere_dados (array a)
{
    array d = aloca_mem_array();
    d->elem_type = a->elem_type;
    switch (a->elem_type)
    {
        case INT:
            d->elem_array.elem_inteiro = a->elem_array.elem_inteiro;
            break;
        case REAL:
            d->elem_array.elem_real = a->elem_array.elem_real;
            break;
        case CHAR:
            d->elem_array.elem_char = a->elem_array.elem_char;
            break;
        case STRING:
            strcpy(d->elem_array.elem_string,a->elem_array.elem_string);
            break;
        case VARIAVEL:
            d->elem_array.elem_variavel = a->elem_array.elem_variavel;
            break;
        case ARRAY:
            d = a->elem_array.array_dentro;
            break;
    }
    return d;
}
/**
 * \brief função que faz o operador '~' para arrays.
 * @param a array que queremos realizar a operação.
 * @param dentro_array variavel que diz em que grau estamos em termos de array's.
 */
void get_out_array (array a, int dentro_array)
{
    if(a->dentro_array == dentro_array)
    {
        array a1 = pop_array(a);
        int size = a1->size;
        int i;
        a1++;
        for(i = 1; i < size - 1; i++)
        {
            array d;
            d = transfere_dados(a1);
            if(d->elem_type == ARRAY) reduz_dentro_array(d);
            push_array(a,d);
            a1++;
        }
    }
    else
        get_out_array(a[a->size-1].elem_array.array_dentro,dentro_array);
}

/**
 * \brief função que realiza a operação '~' para inteiros.
 * @param d Elemento que vamos operar.
 * @param stack Stack atual.
 * @param N Endereço do comprimento da stack atual.
 */
void negacao (DADOS d, DADOS *stack, int *N)
{
    d.dados.numero_inteiro = ~d.dados.numero_inteiro;
    push(stack,N,d,INT);
}

/**
 * \brief função que faz a operação '~'.
 * @param stack Stack atual.
 * @param N Endereço do comprimento da stack atual.
 * @param dentro_array variavel que diz o grau em que estamos do array.
 */
void get_out (DADOS *stack, int *N, int dentro_array)
{
    if (dentro_array ==0)
    {
        DADOS d = pop (stack,N);
        if(d.type != ARRAY)
            negacao(d,stack,N);
        else
        {
            int i;
            int size = d.dados.Array_stack->size-1;
            d.dados.Array_stack++;
            for (i=1;i< size;i++)
            {
                DADOS elem;
                elem = convert_array_dados(d.dados.Array_stack);
                if(elem.type == ARRAY) reduz_dentro_array(elem.dados.Array_stack);
                push (stack, N, elem, elem.type);
                d.dados.Array_stack++;
            }
        }
    }
    else
        get_out_array(stack[(*N)-1].dados.Array_stack,dentro_array);
}
/**
 * \briefMuda um array quando tiramos o elemento que está na ultima posição.
 * @param a array ao qual queremos operar.
 * @return Array depois de efetuar a mudança.
 */
array changeArrayLast(array a){
    a[a->size-2].elem_type = ARRAY;
    a[a->size-2].elem_array.elem_char = ']';
    a->size--;
    return a;
}
/**
 * \brief Muda um array quando tiramos o elemento que está no topo.
 * @param a array ao qual queremos operar.
 * @return Array depois de efetuar a mudança.
 */
array changeArray(array a)
{
    array s = aloca_mem_array();
    s = a;
    s[1].elem_array.elem_start_end = '[';
    s[1].dentro_array = a->dentro_array;
    s[1].elem_type = ARRAY;
    s->size--;
    s++;
    return s;
}
/**
 * \brief coloca num array o primeiro elemento da string que está na ultima posição.
 * @param a array ao qual queremos operar.
 */
void coloca_char_array (array a)
{
    char *t;
    t = a[a->size-1].elem_array.elem_string;
    printf("%s\n",t);
    char s = t[1];
    move_pointer(t);
    array a2 = aloca_mem_array();
    a2->elem_type = CHAR;
    a2->elem_array.elem_char = s;
    a2->dentro_array = a->dentro_array;
    push_array(a,a2);
}

/**
 * \brief coloca num array o primeiro elemento do array que está na ultima posição.
 * @param a array ao qual queremos operar.
 */
void coloca_array_array (array a)
{
    array a1 = pop_array(a);
    print_array(a1);
    array a2 = aloca_mem_array();
    a2->elem_type = a1[1].elem_type;
    a2->elem_array = a1[1].elem_array;
    a2->dentro_array = a->dentro_array;
    array a3 = changeArray(a1);
    a3->size = a1->size;
    push_array(a,a3);
    push_array(a,a2);
}
/**
 * \brief coloca na stack o primeiro elemento do array.
 * @param stack Stack atual.
 * @param N Endereço do comprimento da stack atual.
 */
void coloca_char_stack (DADOS *stack, int *N)
{
    DADOS d1 = pop(stack,N);
    char s = d1.dados.string[1];
    move_pointer(d1.dados.string);
    push(stack,N,d1,STRING);
    d1.dados.caracter = s;
    push(stack,N,d1,CHAR);
}
/**
 * \brief coloca na stack o primeiro elemento do array.
 * @param stack Stack atual.
 * @param N Endereço do comprimento da stack atual.
 */
void coloca_array_stack (DADOS *stack, int *N)
{
    DADOS d1 = pop(stack,N);
    array s = aloca_mem_array();
    s->elem_type  = d1.dados.Array_stack[1].elem_type;
    s->elem_array = d1.dados.Array_stack[1].elem_array;
    DADOS d3;
    d3.dados.Array_stack = changeArray(d1.dados.Array_stack);
    d3.dados.Array_stack->size = d1.dados.Array_stack->size;
    push(stack,N,d3,ARRAY);
    DADOS d2 = convert_array_dados(s);
    push(stack,N,d2,d2.type);
}

/**
 * \brief Operador '(' para operar dentro de arrays
 * @param a array ao qual queremos operar
 * @param dentro_array variavel que diz em que grau esta o array.
 */
void operador_abre_par_array (array a, int dentro_array)
{
    if(a->dentro_array == dentro_array)
    {
        array a1 = pop_array(a);
        switch (a1->elem_type)
        {
            case INT:
                a1->elem_array.elem_inteiro = dados_array(a1) - 1;
                push_array(a,a1);
                break;
            case REAL:
                a1->elem_array.elem_real = dados_array(a1) - 1;
                push_array(a,a1);
                break;
            case CHAR:
                a1->elem_array.elem_char = dados_array(a1) - 1;
                push_array(a,a1);
                break;
            case STRING:
                coloca_char_array(a);
                break;
            case ARRAY:
                coloca_array_array(a);
                break;
            case VARIAVEL:
                break;
            }
    }
    else
        operador_abre_par_array(a[a->size-1].elem_array.array_dentro,dentro_array);
}

/**
 * \brief função que decide o que vai fazer quando lê o operador '('
 * @param stack Stack atual.
 * @param N Endereço do comprimento da stack.
 * @param dentro_array variavel que diz em que grau esta o array.
 */
void operador_abre_parentes (DADOS *stack,int *N, int dentro_array)
{
    if(dentro_array == 0)
    {
        if(stack[(*N)-1].type != ARRAY && stack[(*N)-1].type != STRING)
            decrementa(stack,N,stack[(*N)-1].type);
        else if (stack[(*N)-1].type == STRING)
            coloca_char_stack(stack,N);
        else
            coloca_array_stack(stack,N);
    }
    else
        operador_abre_par_array(stack[(*N)-1].dados.Array_stack,dentro_array);
}
/**
 * \brief coloca na stack o ultimo elemento da string.
 * @param stack Stack atual.
 * @param N Endereço do comprimento da stack atual.
 */
void coloca_char_stack_f (DADOS *stack, int *N)
{
    DADOS d1 = pop(stack,N);
    char s = d1.dados.string[strlen(d1.dados.string)-2];
    d1.dados.string[strlen(d1.dados.string)-2] = d1.dados.string[strlen(d1.dados.string)-1];
    d1.dados.string[strlen(d1.dados.string)-1] = '\0';
    push(stack,N,d1,STRING);
    d1.dados.caracter = s;
    push(stack,N,d1,CHAR);
}

/**
 * \brief coloca na stack o ultimo elemento do array.
 * @param stack Stack atual.
 * @param N Endereço do comprimento da stack atual.
 */
void coloca_array_stack_f (DADOS *stack, int *N)
{
    DADOS d1 = pop(stack,N);
    array s = aloca_mem_array();
    s->elem_type  = d1.dados.Array_stack[d1.dados.Array_stack->size-2].elem_type;
    s->elem_array = d1.dados.Array_stack[d1.dados.Array_stack->size-2].elem_array;
    changeArrayLast(d1.dados.Array_stack);
    push(stack,N,d1,ARRAY);
    d1 = convert_array_dados(s);
    push(stack,N,d1,d1.type);
}

/**
 * \brief coloca no array o ultimo elemento de um array que está dentro do array.
 * @param a array em que estamos a operar.
 * @param dentro_array variavel que diz em que grau esta o array.
 */
void operador_fecha_par_array (array a, int dentro_array)
{
    if(a->dentro_array == dentro_array)
    {
        array a1 = pop_array(a);
        switch (a1->elem_type)
        {
            case INT:
                a1->elem_array.elem_inteiro = dados_array(a1) + 1;
                push_array(a,a1);
                break;
            case REAL:
                a1->elem_array.elem_real = dados_array(a1) + 1;
                push_array(a,a1);
                break;
            case CHAR:
                a1->elem_array.elem_char = dados_array(a1) + 1;
                push_array(a,a1);
                break;
            case STRING:
                coloca_char_array(a);
                break;
            case ARRAY:
                coloca_array_array(a);
                break;
            case VARIAVEL:
                break;
        }
    }
    else
        operador_fecha_par_array(a[a->size-1].elem_array.array_dentro,dentro_array);
}
/**
 * \brief função que decide o que vai fazer quando lê o operador ')'
 * @param stack Stack atual.
 * @param N Endereço do comprimento da stack.
 * @param dentro_array variavel que diz em que grau esta o array.
 */
void operador_fecha_parentes (DADOS *stack,int *N, int dentro_array)
{
    if(dentro_array == 0)
    {
        if(stack[(*N)-1].type != ARRAY && stack[(*N)-1].type != STRING)
            incrementa(stack,N,stack[(*N)-1].type);
        else if (stack[(*N)-1].type == STRING)
            coloca_char_stack_f(stack,N);
        else
            coloca_array_stack_f(stack,N);
    }
    else
        operador_fecha_par_array(stack[(*N)-1].dados.Array_stack,dentro_array);
}
/**
 * \brief função que pega a string para darmos push a um array.
 * @param s String á qual queremos limitar.
 * @param pos pos de s que queremos parar.
 * @param token String final.
 * @return Token.
 */
char *get_string(char *s, int pos, char *token)
{
    int i;
    token[0] = '"';
    for(i = 0; i < pos + 1 && *s != '\0'; i++)
    {
        token[i] = *s;
        s++;
    }
    token[i] = '"';
    return token;
}
/**
 * \brief Move o pointer de uma string n posições.
 * @param s String que queremos mover o pointer.
 * @param pos numero de posições a mexer.
 */
void move_pointer_n (char *s, int pos)
{
    int i;
    if(*s == '"') i = 1;
    else i = 0;
    for(;s[i] != '\0'; i++)
    {
        s[i] = s[i+pos];
    }
}
/**
 * \brief Operador '/' para string.
 * @param a array ao qual vamos separar as string.
 * @param s1 STring que queremos separar.
 * @param s2 String que faz a divião.
 * @param dentro_array variavel que diz em que grau esta o array.
 */
void coloca_array (array a, char *s1, char *s2, int dentro_array)
{
    char token[50];
    int pos = procura_string(s1,s2);
    while (pos != -1)
    {
        s1[strlen(s1)] = '"';
        get_string(s1,pos,token);
        move_pointer_n(s1,pos + strlen(s2) - 1);
        if(dentro_array > 1) token[strlen(token)-1] = '\0';
        push_elem_array(a,dentro_array,STRING,token);
        s2[strlen(s2)] = '"';
        pos = procura_string(s1,s2);
    }
    s1[strlen(s1)] = '"';
    if (strcmp(s1,"\"\"") != 0) push_elem_array(a,dentro_array,STRING,s1);
    push_elem_array(a,dentro_array,STRING,"]");
}
/**
 * \brief função que faz o operador '/' quando estamos dentro de um array.
 * @param a array que estamos a atuar.
 * @param dentro_array variavel que diz em que grau esta o array.
 */
void operador_divisao_array (array a, int dentro_array)
{
    if (a->dentro_array == dentro_array)
    {
        array a1 = pop_array(a);
        array a2 = pop_array(a);
        if (a1->elem_type == INT && a2->elem_type == INT)
        {
            a1->elem_array.elem_inteiro = a2->elem_array.elem_inteiro / a1->elem_array.elem_inteiro;
            push_array(a,a1);
        }
        else if (a1->elem_type != STRING && a2->elem_type != STRING)
        {
            double x = dados_array(a1);
            double y = dados_array(a2);
            array_double(a,y/x);
        }
        else if (strlen(a1->elem_array.elem_string) > 2)
        {
            dentro_array++;
            a[a->size].elem_array.array_dentro = aloca_mem_array();
            inicia_array(a, dentro_array);
            a->size++;
            coloca_array(a[a->size-1].elem_array.array_dentro,a2->elem_array.elem_string,a1->elem_array.elem_string,dentro_array);
        }
        else
            push_array(a,a2);
    } else
        operador_divisao_array(a[a->size-1].elem_array.array_dentro,dentro_array);
}

/**
 * \brief função que inicia um array na stack.
 * @param stack Stack atual.
 * @param N Endereço do comprimento da stack atual.
 */
void elem_stack_array (DADOS *stack, int *N)
{
    stack[*N].dados.Array_stack = aloca_mem_array();
    stack[*N].dados.Array_stack[0].size = 1;
    stack[*N].type = ARRAY;
    stack[*N].dados.Array_stack[0].dentro_array = 1;
    stack[*N].dados.Array_stack[0].elem_type = ARRAY;
    stack[*N].dados.Array_stack[0].elem_array.elem_start_end = '[';
    (*N)++;
}
/**
 * \brief função que decide qual operação vai realizar no operador '/'.
 * @param stack Stack atual.
 * @param N Endereço do comprimento da stack atual.
 * @param dentro_array variavel que diz em que grau esta o array.
 */
void operador_divisao (DADOS *stack,int *N, int dentro_array)
{
    if (dentro_array == 0)
    {
        if(stack[(*N)-1].type != STRING && stack[(*N)-2].type != STRING)
            divisao(stack,N,stack[(*N)-1].type ,stack[(*N)-2].type );
        else
        {
            DADOS d1 = pop(stack,N);
            DADOS d2 = pop(stack,N);
            if (strlen(d1.dados.string) > 2)
            {
                dentro_array++;
                elem_stack_array(stack,N);
                coloca_array(stack[(*N)-1].dados.Array_stack,d2.dados.string,d1.dados.string,dentro_array);
            }
            else
                push(stack,N,d2,STRING);
        }
    }
    else
        operador_divisao_array(stack[(*N)-1].dados.Array_stack,dentro_array);
}

/**
 * \brief função que realiza a operção '$' dentro de array.
 * @param a array que estamos  operar.
 * @param dentro_array variavel que diz em que grau esta o array.
 */
void replica_elem_array (array a, int dentro_array)
{
    if(a->dentro_array == dentro_array)
    {
        array a1;
        a1=pop_array(a);
        a[a->size] = a[a->size- a1->elem_array.elem_inteiro-1];
        a->size++;
    }
    else
        replica_elem_array(a[a->size-1].elem_array.array_dentro,dentro_array);
}

/**
 * \brief função que realiza a operção '$' .
 * @param stack Stack atual.
 * @param N Endereço do comprimento da stack atual.
 * @param dentro_array variavel que diz em que grau esta o array.
 */
void operador_dolar (DADOS *stack, int *N, int dentro_array)
{
    if(dentro_array == 0)
        replica_elem(stack,N);
    else
        replica_elem_array(stack[(*N)-1].dados.Array_stack,dentro_array);
}

/**
 * \brief função que realiza a operação '_' dentro de array.
 * @param a array que queremos trabalhar.
 * @param dentro_array variavel que diz em que grau esta o array.
 */
void operador_under_array(array a, int dentro_array)
{
    if(a->dentro_array == dentro_array)
    {
        array a1;
        a1 = pop_array(a);
        push_array(a,a1);
        push_array(a,a1);
    }
    else
        operador_under_array(a[a->size-1].elem_array.array_dentro,dentro_array);
}

/**
 * \brief função que realiza a operação '_'.
 * @param stack Stack atual.
 * @param N Endereço da stack atual.
 * @param dentro_array variavel que diz em que grau esta o array.
 */
void operador_underscore (DADOS *stack, int *N, int dentro_array)
{
    if(dentro_array == 0)
        push(stack, N, stack[(*N) - 1], stack[(*N) - 1].type);
    else
        operador_under_array(stack[(*N)-1].dados.Array_stack,dentro_array);
}
/**
 * \brief função que aplica o operador 'N/' para arrays
 * @param a array que estamos a operar
 * @param dentro_array variavel que diz em que grau esta o array.
 */
void operadornbar_array (array a, int dentro_array)
{
    if(a->dentro_array == dentro_array)
    {
        array a1 = pop_array(a);
        dentro_array++;
        a[a->size].elem_array.array_dentro = aloca_mem_array();
        inicia_array(a, dentro_array);
        a->size++;
        char s[3] = "\"\n\"";
        coloca_array(a[a->size-1].elem_array.array_dentro,a1->elem_array.elem_string,s,dentro_array);
    }
    else
        operadornbar_array(a[a->size-1].elem_array.array_dentro,dentro_array);
}
/**
 * \brief função que decide o que faz quando lê o token 'N/'
 * @param stack Stack atual.
 * @param N Endereço do comprimento da stack atual.
 * @param dentro_array variavel que diz em que grau esta o array.
 */
void operadornbarra (DADOS *stack, int *N, int dentro_array)
{
    if (dentro_array == 0)
    {
        DADOS d1 = pop(stack,N);
        dentro_array++;
        elem_stack_array(stack,N);
        char s[3] = "\"\n\"";
        coloca_array(stack[(*N)-1].dados.Array_stack,d1.dados.string,s,dentro_array);
    }
    else
        operadornbar_array(stack[(*N)-1].dados.Array_stack,dentro_array);
}

/**
 * \brief função que esvazia uma string.
 * @param s string que queremos esvaziar.
 */
void esvazia_token(char *s)
{
    int i;
    for(i = 1; s[i]!='\0';i++)s[i] = '\0';
}

/**
 * \brief Operador '/' para string.
 * @param a array ao qual vamos separar as string.
 * @param s1 STring que queremos separar.
 * @param dentro_array variavel que diz em que grau esta o array.
 */
void coloca_array_s (array a, char *s, int dentro_array)
{
    char token[50];
    int i;
    token [0] = '"';
    int j = 1;
    for(i = 1; s[i]!= '\0';i++)
    {
        if(s[i] != ' ' && s[i] != '\n')
        {
            token[j] = s[i];
            j++;
        }
        else
        {
            if(strlen(token) > 1)
            {
                token[j] = '"';
                push_elem_array(a,dentro_array,STRING,token);
                esvazia_token(token);
            }
            token[0] = '"';
            j = 1;
        }
    }
    if(j > 1)
        push_elem_array(a,dentro_array,STRING,token);
    push_elem_array(a,dentro_array,STRING,"]");
}

/**
 * \brief função que aplica o operador 'S/' para arrays
 * @param a array que estamos a operar
 * @param dentro_array variavel que diz em que grau esta o array.
 */
void operadorsbar_array (array a, int dentro_array)
{
    if(a->dentro_array == dentro_array)
    {
        array a1 = pop_array(a);
        dentro_array++;
        a[a->size].elem_array.array_dentro = aloca_mem_array();
        inicia_array(a, dentro_array);
        a->size++;
        coloca_array_s(a[a->size-1].elem_array.array_dentro,a1->elem_array.elem_string,dentro_array);

    }
    else
        operadorsbar_array(a[a->size-1].elem_array.array_dentro,dentro_array);
}

/**
 * \brief função que decide o que faz quando lê o token 'S/'
 * @param stack Stack atual.
 * @param N Endereço do comprimento da stack atual.
 * @param dentro_array variavel que diz em que grau esta o array.
 */
void operadorsbarra (DADOS *stack, int *N, int dentro_array)
{
    if (dentro_array == 0)
    {
        DADOS d1 = pop(stack,N);
        dentro_array++;
        elem_stack_array(stack,N);
        coloca_array_s(stack[(*N)-1].dados.Array_stack,d1.dados.string,dentro_array);
    }
    else
        operadorsbar_array(stack[(*N)-1].dados.Array_stack,dentro_array);
}

/**
 * \brief converte um elemento do tipo array para string.
 * @param a array que queremos converter.
 * @param l destino da string.
 * @return A string final.
 */
char *convert_string_array (array a, char *l)
{
    switch (a->elem_type)
    {
        case INT:
            sprintf(l,"%ld",a->elem_array.elem_inteiro);
            break;
        case REAL:
            sprintf(l,"%.6g",a->elem_array.elem_real);
            break;
        case CHAR:
            sprintf(l,"%c",a->elem_array.elem_char);
            break;
        case VARIAVEL:
            break;
        case STRING:
            break;
        case ARRAY:
            break;
    }
    a->elem_type = STRING;
    move_pointer_frente(l);
    l[0] = '"';
    l[strlen(l)] = '"';
    return l;
}
/**
 * \brief função que converte o ultimo elemento de um array para string.
 * @param a array que estamos a operar.
 * @param dentro_array variavel que diz em que grau esta o array.
 */
void operador_s_array (array a, int dentro_array)
{
    if(a->dentro_array == dentro_array)
    {
        array a1 = pop_array(a);
        convert_string_array(a1,a1->elem_array.elem_string);
        push_array(a,a1);
    }
    else
        operador_s_array(a[a->size-1].elem_array.array_dentro,dentro_array);
}

/**
 * \brief função que converte o ultimo elemento para string.
 * @param stack Stack atual.
 * @param N Endereço do comprimento atual da stack.
 * @param dentro_array variavel que diz em que grau esta o array.
 */
void operador_s (DADOS *stack, int *N, int dentro_array)
{
    if(dentro_array == 0)
    {
        DADOS d1 = pop(stack,N);
        convert_string(d1,d1.dados.string);
        push(stack,N,d1,STRING);
    }
    else operador_s_array(stack[(*N)-1].dados.Array_stack,dentro_array);
}