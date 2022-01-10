/**
 * @file Ficheiro que contém as funções que trabalham com a stack e a struct que define a stack.
 */

#ifndef GUIAO2_STACK_H
#define GUIAO2_STACK_H

#endif //GUIAO2_STACK_H

/**
 * Tipo de cada elemento da stack
 */
typedef enum {
    INT, /**< tipo inteiro */
    REAL, /**< tipo real */
    CHAR, /**< tipo char */
    STRING, /**< tipo string */
    VARIAVEL,  /**< tipo variavel */
    ARRAY /**< tipo array */
} TIPO;

/**
 * Tipo das variaveis
 */
typedef enum{
    INTEIRO, /**< tipo inteiro */
    DOUBLE, /**< tipo real */
    CARACTER, /**< tipo char */
    TEXTO /**< tipo string*/
}TIPO_VARIAVEL;

/**
 * Struct que define cada elemento de um variavel
 */
typedef struct {
    char indentificacao; /**< nome da variavel */
    TIPO_VARIAVEL tipo; /**< tipo da variavel */
    union {
        long variavel_int; /**< tipo inteiro */
        double variavel_real; /**< tipo real */
        char variavel_char; /**< tipo char */
        char variavel_string[500]; /**< tipo string*/
    }tipo_variavel; /**< valor da variavel conforme o tipo */
}tuplo_variavel;

/**
 * Struct que representa os elementos do tipo array.
 */
typedef struct Struct_array {
    TIPO elem_type; /**< Tipo do elemento do array */
    int dentro_array; /**< Variavel que diz o elemento está dentro de um array */
    int size; /**< Size do array */
    union
    {
        char elem_start_end; /**< elemento que diz quando começa ou acaba o array */
        long elem_inteiro; /**< tipo inteiro */
        double elem_real; /**< tipo real */
        char elem_char; /**< tipo char */
        char elem_string[500]; /**< tipo string */
        tuplo_variavel elem_variavel; /**< tipo variavel */
        struct Struct_array *array_dentro; /**< tipo array dentro de array */
    }elem_array; /**< valor do elemento do array conforme o tipo */
} * array;  /**< apontador de um array */

/**
 * Struct que define cada elemento da stack
 */
typedef struct {
    TIPO type; /**< tipo da variavel */
    union {
        long numero_inteiro; /**< tipo inteiro */
        double numero_real; /**< tipo real */
        char caracter; /**< tipo char */
        char string[600]; /**< tipo string */
        tuplo_variavel variavel; /**< tipo variavel */
        array Array_stack; /**< tipo array */
    }dados; /**< valor do elemento da stack conforme o tipo */
}DADOS;

void push_array (array a, array elem);
int push(DADOS *stack, int *N, DADOS d, TIPO x);

void changennumbers_array (array a, int dentro_array, int n);
void change_nmembers (DADOS *stack, int N, int number);
void changenumbers (DADOS *stack, int *N, int dentro_array, int n);

DADOS pop (DADOS *stack, int *N);
array pop_array (array a);
void operador_pop (array a, int dentro_array);
void operador_ponto_vir (DADOS *stack, int *N, int dentro_array);


void print_array (array Array);
void print_string(char *s);
void print_stack (DADOS *stack, int N);

void negacao (DADOS d, DADOS *stack, int *N);
void soma (DADOS *stack, int *N);
void soma_array (array a, array a1, array a2);
void operador_mais_array (array a,int dentro_array);
void operador_mais (DADOS *stack, int *N, int dentro_array);

void subtracao (DADOS *stack, int *N);
void operador_menos (DADOS *stack, int *N, int dentro_array);
void operador_menos_array (array a, int dentro_array);

void multiplicacao (DADOS *stack, int *N);

void expoente (DADOS *stack, int *N);
void hashtag (DADOS *stack, int *N, int dentro_array);
void hastag_array (array a, int dentro_array);
int procura_string (char *s1, char *s2);

void divisao (DADOS *stack, int *N, TIPO tipo1, TIPO tipo2 );

void resto (DADOS *stack, int *N);
void operador_resto (DADOS *stack, int *N, int dentro_array);
void operador_resto_array (array a, int dentro_array);

void and (DADOS *stack, int *N);
void operador_e (DADOS *stack, int *N, int dentro_array);
void operador_e_array (array a, int dentro_array);

void or (DADOS *stack, int *N);
void operador_or_array (array a, int dentro_array);
void operador_or (DADOS *stack, int *N, int dentro_array);

void xor (DADOS *stack, int *N);
void operador_xor (DADOS *stack, int *N, int dentro_array);
void operador_xor_array (array a, int dentro_array);

void operador_exclamacao (DADOS *stack, int *N, int dentro_array);

void incrementa (DADOS *stack, int *N, TIPO tipo1);

void decrementa (DADOS *stack, int *N, TIPO tipo1);

void equal (DADOS *stack, int *N);

void bigger (DADOS *stack, int *N);

void minor (DADOS *stack, int *N);
void operador_menor (DADOS *stack, int *N, int dentro_array);
void operador_minor_array (array a, int dentro_array);

void change_bool_array (array a, int dentro_array);
void change_bool(DADOS *stack, int *N);

void log_e_array (array a, int dentro_array);
void log_ou_array (array a, int dentro_array);
void log_men_array (array a, int dentro_array);
void log_mai_array (array a, int dentro_array);
void logica_e (DADOS *stack, int *N, int dentro_array);
void logica_ou (DADOS *stack, int *N, int dentro_array);
void logica_menor (DADOS *stack, int *N, int dentro_array);
void logica_maior (DADOS *stack, int *N, int dentro_array);

void if_then_else(DADOS *stack, int *N);
void operador_interrogacao (DADOS *stack, int *N, int dentro_array);
void operador_inte_array (array a, int dentro_array);

void converte_int_array (array a, int dentro_array);
void converte_int (DADOS *stack, int *N, int dentro_array);

void converte_double_array (array a, int dentro_array);
void converte_real (DADOS *stack, int *N, int dentro_array);

void converte_char_array (array a, int dentro_array);
void converte_char (DADOS *stack, int *N, int dentro_array);

void ler_linha (DADOS *stack, int *N, int dentro_array);

void inicializa_array (tuplo_variavel *array_var);
void atualiza_array (tuplo_variavel *array_var, char c, DADOS d);
void atualiza_valor (DADOS *stack, int pos, DADOS d1);
void push_variavel_array (array a, int dentro_array, char c, tuplo_variavel *array_var);
void push_variavel (DADOS *stack, int *N, DADOS d1, char va);
void push_variavel_omissao (DADOS *stack, int *N, char c, tuplo_variavel *array_var);

void associa_valor (DADOS *stack, int *N, char c, int pos, tuplo_variavel *array_var);
void associa_valor_array (array a, int dentro_array, char c, tuplo_variavel *array_var);
void add_var_value (DADOS *stack, int *N, char c, tuplo_variavel *array_var, int dentro_array);

int variavel_definida (DADOS *stack, char c, int N);

void print_variavel (tuplo_variavel v);

double dados_variavel (DADOS d);

void push_resultado (double resultado, DADOS *stack, int *N);

void replica_elem (DADOS *stack, int *N);

void nxttoken(char token[],DADOS *stack,int *N,int dentro_array);

DADOS verifica_numero (char *token);

void push_elem_array (array a, int dentro_array, TIPO tipo_array, char *token);

void push_numero (DADOS *stack, int *N, char *token, int dentro_array);

array aloca_mem_array ();
array inicia_array (array a, int dentro_array);

void push_char (DADOS *stack,int *N, char *token, int dentro_array);
void push_string (DADOS *stack,int *N, char *token, int dentro_array);

void acrescenta_inicio (array a, array elem);
void muda_tipo (array a, array elem);
double dados_array (array a);
void array_double (array a_push,double res);
array concat_array (array a, array b);
array dados_para_array (DADOS d);

void operador_minor_array (array a, int dentro_array);

array multiplica_array (array a, int vezes);
void operador_vezes_array (array a,int dentro_array);
void operador_vezes (DADOS *stack, int *N, int dentro_array);

char *get_string(char *s, int pos, char *token);
void move_pointer_n (char *s, int pos);
void coloca_array (array a, char *s1, char *s2, int dentro_array);
void operador_divisao_array (array a, int dentro_array);
void elem_stack_array (DADOS *stack, int *N);
void operador_divisao (DADOS *stack,int *N, int dentro_array);

void operador_igual_array (array a, int dentro_array);
void operador_igual (DADOS *stack,int *N, int dentro_array);

void operador_bigger_array (array a, int dentro_array);
void operador_bigger (DADOS *stack, int *N, int dentro_array);

void tamanho_range (DADOS *stack, int *N, int dentro_array);
void range (array elem, int size,int dentro_array);
void tamanho_range_array (array a, int dentro_array);

int minor_strings (char *s1,char *s2);
int bigger_strings (char *s1,char *s2);
char *multiplica_string (char *s, int vezes);
void move_pointer_frente (char *s);
char *move_pointer (char *s);

void get_out_array (array a, int dentro_array);
void get_out (DADOS *stack, int *N, int dentro_array);


array changeArray(array a);
array changeArrayLast(array a);

void ler_input(DADOS *stack, int *N, int dentro_array);

void replica_elem_array (array a, int dentro_array);
void operador_dolar (DADOS *stack, int *N, int dentro_array);

void coloca_char_array (array a);
void coloca_array_array (array a);

void coloca_char_stack (DADOS *stack, int *N);
void coloca_array_stack (DADOS *stack, int *N);

void operador_under_array(array a, int dentro_array);
void operador_underscore (DADOS *stack, int *N, int dentro_array);

void operador_abre_par_array (array a, int dentro_array);
void operador_abre_parentes (DADOS *stack,int *N, int dentro_array);

void coloca_char_stack_f (DADOS *stack, int *N);
void coloca_array_stack_f (DADOS *stack, int *N);

void operador_fecha_par_array (array a, int dentro_array);
void operador_fecha_parentes (DADOS *stack,int *N, int dentro_array);

void operadornbar_array (array a, int dentro_array);
void operadornbarra (DADOS *stack, int *N, int dentro_array);

void operadorsbar_array (array a, int dentro_array);
void operadorsbarra (DADOS *stack, int *N, int dentro_array);

array transfere_dados (array a);
void reduz_dentro_array (array a);
double double_var (tuplo_variavel v);
void converte_dados_var (array a);
DADOS convert_array_dados (array a);
TIPO converte_tipo_var (tuplo_variavel var);
tuplo_variavel converte_dados_variavel (DADOS d);
TIPO_VARIAVEL converte_tipo (TIPO d);

void remove_elem (DADOS *stack, int *N, int pos);

void operador_s_array (array a, int dentro_array);
void operador_s (DADOS *stack, int *N, int dentro_array);
char *convert_string (DADOS d, char *l);
char *convert_string_array (array a, char *l);


void concats_strings (array a, array a1, array a2);
void concat_arrays (array a, array a1, array a2);
void concat_string_stack (DADOS *stack, int *N);
void concat_array_stack (DADOS *stack, int *N);

void get_n_elem_array_array (array a);
void get_n_elem_string_array (array a);

void cmp_string_array (array a);
void cmp_string_stack (DADOS *stack, int *N);

void array_equal (array a);

void get_elem_n_array (DADOS *stack, int *N);
void get_elem_n_string (DADOS *stack, int *N);
void get_elem_n_var (DADOS *stack, int *N);


