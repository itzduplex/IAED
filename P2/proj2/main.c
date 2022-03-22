#include "lowend.h"
#include "highend.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* Nome: Goncalo Nuno Branco Gaspar Antunes */
/* Numero: 93716 */

/* No main cria-se inicialmente a lista e o array de pointers para separar e analisar o input, que é obtido a partir do fgets, posteriormente e chamada
cada funcao dependendo desse input. */

int main(){
    char buffer[MAX_STR], *p[MAX_PTR];
    Lista *list = initList();
    T_List **table = initTable(), **domain = initTable();

    while(1){
        fgets(buffer, MAX_STR, stdin);
        parseInput(buffer, p);
        switch (p[0][0]){
            case 'a':
            addContact(list, table, domain, p);
            break;

            case 'l':
            printAllContacts(list);
            break;

            case 'p':
            findContact(table, p);
            break;

            case 'r':
            removeContact(table, domain, list, p);
            break;

            case 'e':
            changeDomain(table, domain, p);
            break;

            case 'c':
            countDomain(domain, p);
            break;

            case 'x':
            freeLista(list);
            freeTable(domain);
            freeTable(table);
            return 0;
        }
    }
}