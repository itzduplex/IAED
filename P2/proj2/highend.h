#ifndef HIGH_LEVEL_FUNCTIONS
#define HIGH_LEVEL_FUNCTIONS
#include "lowend.h"

/* Nome: Goncalo Nuno Branco Gaspar Antunes */
/* Numero: 93716 */

void addContact(Lista *list, T_List **table, T_List **domain, char *p[]);

void printAllContacts(Lista *list);

void findContact(T_List **table, char *p[]);

void removeContact(T_List **table, T_List **domain, Lista *list, char *p[]);

void changeDomain(T_List **table, T_List **domain, char *p[]);

void countDomain(T_List **domain, char *p[]);

#endif