#ifndef LOW_END_FUNCTIONS
#define LOW_END_FUNCTIONS
#define NAME_ERROR "Nome existente.\n"
#define NO_NAME_ERROR "Nome inexistente.\n"
#define MAX_STR 1602 /* Tamanho total possivel de uma string */
#define MAX_PTR 5
#define MAX_HASH 613

/* Nome: Goncalo Nuno Branco Gaspar Antunes */
/* Numero: 93716 */

typedef struct node {
    struct node *next, *previous;
    char *nome, *email, *dom, *num;
} Contacto;

typedef struct list {
    Contacto *head, *last;
} Lista;

typedef struct t_node{
    Contacto *cont;
    struct t_node *next, *previous;
} Node;

typedef struct table{
    Node *head, *last;
} T_List;

Lista * initList();

void initList_T(T_List *list);

T_List ** initTable();

int hash(char *c);

void parseInput(char s[], char *p[]);

Contacto * assignContact(char *p[]);

void pushContact(Contacto *new, Lista *list);

Node * assignNode(Contacto *c);

void pushNode(Node *new, T_List *table);

Node * contactExists(T_List *list, char *s);

void removeNode(Node *aux, T_List *table);

void removeContactFromList(Contacto *aux, Lista *list);

void printContact(Contacto *aux);

void freeContact(Contacto *new);

void freeLista(Lista *list);

void freeTable(T_List **table);

void changeEmail(Contacto *aux, char *e, char *d);

#endif
