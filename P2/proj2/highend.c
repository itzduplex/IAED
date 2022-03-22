#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "highend.h"
#include "lowend.h"

/* Nome: Goncalo Nuno Branco Gaspar Antunes */
/* Numero: 93716 */

/* A funcao addContact recebe um ponteiro do tipo lista e um array de ponteiros que possui os elementos necessarios a adicionar a cada Contacto, sendo que
esses elementos estao em p[1] - nome, p[2] e p[3] - email e dominio, p[4] - numero de telefone. */

void addContact(Lista *list, T_List **table, T_List **domain, char *p[]){
    int aux = hash(p[1]), x = hash(p[3]);
    Contacto *new;
    Node *n1, *n2;
    
    if (!contactExists(table[aux], p[1])){                   /* Se o contacto a adicionar nao esta na hash-table, coloca-se em ambas as hash-tables e na */
        new = assignContact(p);                              /* lista duplamente ligada. */
        n1 = assignNode(new);                                /* Iniciam-se dois nodes diferentes que apontam para o contacto recem-criado. */
        n2 = assignNode(new);
        pushContact(new, list);                                     
        pushNode(n1, table[aux]);
        pushNode(n2, domain[x]); 
        return;
    }
    printf(NAME_ERROR);
}

/* A funcao printAllContacts recebe um ponteiro do tipo Lista e imprime quaisquer contactos que existam nela, 
circulando desde a cabeca da lista ate o ponteiro ser nulo */

void printAllContacts(Lista *list){
    Contacto *aux;
    for (aux = list->head; aux; aux = aux->next) printContact(aux);
}

/* A funcao findContact recebe um ponteiro do tipo Lista e um array de ponteiros que contem o nome a procurar, 
procura na lista por um Contacto com o mesmo nome, se o encontrar, imprime o nome, email e telefone desse contacto, caso contrario, imprime erro. */

void findContact(T_List **table, char *p[]){
    Node *aux;
    int x = hash(p[1]);

    if ((aux = contactExists(table[x], p[1]))){
        printContact(aux->cont);
        return;
    }
    printf(NO_NAME_ERROR);
}

/* A funcao removeContact recebe um ponteiro do tipo Lista e um array de ponteiros, verifica se o contacto com o nome a procurar existe, 
caso contrario imprime mensagem de erro. Verifica se o elemento a remover e a cabeca da lista, se for, retira-se esse elemento da lista e 
liberta-se a sua memoria alocada, caso contrario, significa que o contacto tem dois vizinhos, e tem que se o retirar de la para o poder 
libertar a memoria. Depois, verifica-se se o contacto e o ultimo da lista, se for, retira-se simplesmente a ligacao ao elemento
anterior, caso contrario, vai ter que se retirar a informacao que o liga ao anterior e ao aferente. Posteriormente, 
liberta-se a memoria alocada pelo contacto. */

void removeContact(T_List **table, T_List **domain, Lista *list, char *p[]){
    Node *aux, *aux1;
    int x = hash(p[1]), y;
    if (!(aux = contactExists(table[x], p[1]))){
        printf(NO_NAME_ERROR);
        return;
    }

    y = hash(aux->cont->dom);
    aux1 = contactExists(domain[y], aux->cont->nome);   /* Vai-se buscar o node da hash-table dos domains. */

    removeContactFromList(aux->cont, list);             /* Remove-se o contacto da lista duplamente ligada. */
    removeNode(aux, table[x]);                          /* Removem-se os Nodes de ambas as hash-tables e da lista duplamente ligada organizada */
    removeNode(aux1, domain[y]);
}

/* A funcao changeDomain recebe um ponteiro do tipo Lista e um array de ponteiros contendo a informacao do nome e do novo email, e 
vai verificar se existe um contacto com esse nome, caso nao exista imprime erro, e altera-se a memoria alocada pelo ponteiro do email 
para a necessaria a guardar o novo email, que e depois copiado para o contacto. */

void changeDomain(T_List **table, T_List **domain, char *p[]){
    Node *aux, *aux1;
    int x = hash(p[1]), y, z = hash(p[3]);
    if (!(aux = contactExists(table[x], p[1]))){
        printf(NO_NAME_ERROR);
        return;
    }
    y = hash(aux->cont->dom);                                   /* Remove-se o node da hash-table, de modo a poder alterar o email do contacto associado a esse node, */
    aux1 = contactExists(domain[y], aux->cont->nome);           /* cria-se um novo node com o novo dominio e coloca-se esse node nessa hash */
    removeNode(aux1, domain[y]);

    changeEmail(aux->cont, p[2], p[3]);
    
    aux1 = assignNode(aux->cont);
    pushNode(aux1, domain[z]);
}

/* A funcao countDomain recebe um ponteiro do tipo Lista e um array de ponteiros contendo o dominio. Procura-se na hashtable dos dominios quaisquer elementos 
com um dominio igual ao fornecido e cada vez que o dominio e igual incrementa-se uma unidade ao contador. */

void countDomain(T_List **table, char *p[]){
    Node *aux;
    int counter = 0, x = hash(p[1]);

    for (aux = table[x]->head; aux; aux = aux->next){
        if (!strcmp(aux->cont->dom, p[1])){       
            counter++;
        }
    }
    printf("%s:%d\n", p[1], counter);
}