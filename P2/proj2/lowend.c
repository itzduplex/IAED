#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "lowend.h"

/* Nome: Goncalo Nuno Branco Gaspar Antunes */
/* Numero: 93716 */

/* Ambas as funcoes servem simplesmente para embelezar o codigo, apenas atribuem a cabeca e o fim de uma lista duplamente ligada e 
de uma lista de table a apontar para NULL. */

Lista * initList(){
    Lista *list = malloc(sizeof(Lista));
    list->head = list->last = NULL;
    return list;
}

void initList_T(T_List *list){
    list->head = list->last = NULL;
}

/* Inicia-se o array de tables, com tanto a cabeca como o fim a apontar para NULL. */

T_List ** initTable(){
    T_List **table = malloc(sizeof(T_List) * MAX_HASH);
    int x;
    for (x = 0; x < MAX_HASH; x++) {
        table[x] = malloc(sizeof(T_List));
        initList_T(table[x]);    
    }
    return table;
}

/* A funcao recebe um char e devolve uma chave de hash table, calculando fazendo a soma de caracteres seguidos do resto da divisao pelo tamanho
da tabela. A hash vai ser a chave a que determinado node pertence (nome para a T_List table, dominio para a T_List domain). */

int hash(char *c){
    int l = 0, r = 127, size = MAX_HASH;
    for (; *c != '\0'; c++){
        l = (r * l + *c) % size;
    }
    return l;
}

/* A funcao recebe um array de chars e vai separar cada string num pointer, alocado num array de pointers, sendo que as strings sao divididas por conterem
entre elas ou um caracter de espaco ou um \n. */

void parseInput(char s[], char **p){
    char *token;
    int i = 0;
    token = strtok(s, " @\n");

    for (i = 0; i < MAX_PTR; i++){    
        p[i] = token;
        token = strtok(NULL, " @\n");
    }
}

/* A funcao recebe um contacto e um array de pointers e coloca as informacoes presentes no array de pointers no contacto */

Contacto * assignContact(char *p[]){
    Contacto *new = malloc(sizeof(Contacto));
    new->nome = malloc(sizeof(char) * (strlen(p[1]) + 1));
    new->email = malloc(sizeof(char) * (strlen(p[2]) + 1));
    new->dom = malloc(sizeof(char) * (strlen(p[3]) + 1));
    new->num = malloc(sizeof(char) * (strlen(p[4]) + 1));

    new->next = new->previous = NULL;

    strcpy(new->nome, p[1]);
    strcpy(new->email, p[2]);
    strcpy(new->dom, p[3]);
    strcpy(new->num, p[4]);
    return new;
}

/* A funcao coloca um contacto new no fim da lista */

void pushContact(Contacto *new, Lista *list){
    new->previous = list->last;
    if (list->last) list->last->next = new;
    list->last = new;
    if (!list->head) list->head = new;
}

/* Atribuem-se os valores supostos num node, atribuindo o proximo e o anterior a NULL e o contacto a apontar pelo node. */

Node * assignNode(Contacto *c){
    Node *new = malloc(sizeof(Node));
    new->next = new->previous = NULL;
    new->cont = c;
    return new;
}

/* Coloca-se um node no fim de uma table. */

void pushNode(Node *new, T_List *table){
    new->previous = table->last;
    if (table->last) table->last->next = new;
    table->last = new;
    if (!table->head) table->head = new;
}

/* A funcao verifica se um contacto com nome s existe na lista *list, e se existir, devolve o ponteiro que aponta para esse contacto */

Node * contactExists(T_List *list, char *s){
    Node *aux;
    for (aux = list->head; aux; aux = aux->next) 
        if (!strcmp(aux->cont->nome, s)) return aux;
    return (aux = NULL);
}

/* Removem-se as ligacoes entre nodes numa table. */

void removeNode(Node *aux, T_List *table){
    if (aux->previous == NULL){
        table->head = aux->next;
    } else {
        aux->previous->next = aux->next;
    }

    if (aux->next == NULL){
        table->last = aux->previous;
    } else {
        aux->next->previous = aux->previous;
    }
    free(aux);
}

/* Removem-se as ligacoes de um contacto de uma lista duplamente ligada. */

void removeContactFromList(Contacto *aux, Lista *list){
    if (aux->previous == NULL){
        list->head = aux->next;
    } else {
        aux->previous->next = aux->next;
    }

    if (aux->next == NULL){
        list->last = aux->previous;
    } else {
        aux->next->previous = aux->previous;
    }
    freeContact(aux);
}

/* A funcao recebe um contacto e imprime o seu nome, email e numero de telefone */

void printContact(Contacto *aux){
    printf("%s %s@%s %s\n", aux->nome, aux->email, aux->dom, aux->num);
}

/* A funcao liberta a memoria toda alocada por um contacto. */

void freeContact(Contacto *new){
    free(new->nome);
    free(new->email);
    free(new->dom);
    free(new->num);
    free(new);
}

/* A funcao liberta a memoria toda alocada por uma lista. */

void freeLista(Lista *list){
    Contacto *aux;
    while(list->head){
        aux = list->head->next;
        freeContact(list->head);
        list->head = aux;
    }
    free(list);
}

/* Circula-se por todos os nodes do array de Tables e libertam-se os nodes. Posteriormente, liberta-se a table, e incrementa-se uma unidade ao counter */

void freeTable(T_List **table){
    int x;
    Node *aux;
    for (x = 0; x < MAX_HASH; x++){
        while (table[x]->head){
            aux = table[x]->head->next;
            free(table[x]->head);
            table[x]->head = aux;
        }
        free(table[x]);
    }
    free(table);
}

/* A funcao changeEmail recebe um contacto, um email e um dominio e realoca-se a memoria do contacto para poder armazenar o novo email e dominio. */

void changeEmail(Contacto *aux, char *e, char *d){
    aux->email = (char*) realloc(aux->email, sizeof(char) * (strlen(e) + 1));
    aux->dom = (char*) realloc(aux->dom, sizeof(char) * (strlen(d) + 1));
    strcpy(aux->email, e);
    strcpy(aux->dom, d);
}

