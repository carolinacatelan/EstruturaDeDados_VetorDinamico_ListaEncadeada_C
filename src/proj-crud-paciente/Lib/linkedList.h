#include <stdlib.h>
#include "../mainLinkedList.h"

#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#ifndef INFO
#define INFO Impressora
#endif

typedef struct no
{
    INFO info;
    struct no *prox;
} No;

int linkedList_size(No *); 
No* linkedList_remove(No **lista , INFO info);
void linkedList_delete(No **lista, int position);
No* linkedList_clear(No *);
No* linkedList_inserirNoInicio(No *, INFO);
No* linkedList_inserirNoFim(No *lista, INFO info);

#endif