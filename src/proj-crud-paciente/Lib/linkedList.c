#include <stdlib.h>
#include "linkedList.h"

int linkedList_size(No *lista)
{
    int cont;

    for (cont = 0; lista != NULL; cont++, lista = lista->prox);

    return cont;
}

No* linkedList_remove(No **lista, INFO info){
    No *aux, *remove = NULL; 

    if(*lista){
        if((*lista)->info.modelo == info.modelo){
            remove = *lista;
            *lista = remove->prox;
        }
        else {
            aux = *lista;
            while (aux->prox && aux->prox->info.modelo != info.modelo)
                aux = aux->prox;
            if(aux->prox){
                remove = aux->prox;
                aux->prox = remove->prox;
            }
        }
    }

    return remove;
}

void linkedList_delete(No **head_ref, int position){
    int i;

    if (*head_ref == NULL)
        return;
 
    No* temp = *head_ref;
 
    if (position == 0) {
 
        *head_ref = temp->prox;
 
        free(temp);
        return;
    }
 
    for (i = 0; temp != NULL && i < position - 1; i++)
        temp = temp->prox;

    if (temp == NULL || temp->prox == NULL)
        return;

    No* prox = temp->prox->prox;
 
    free(temp->prox); 
 
    temp->prox = prox;
}

No *linkedList_clear(No *lista)
{
    No *p;

    while (lista != NULL)
    {
        p = lista;
        lista = lista->prox;
        free(p);
    }

    return NULL;
}

No* linkedList_inserirNoInicio(No *lista, INFO info)
{
    No *p;

    p = (No *)malloc(sizeof *p);
    if (p == NULL)
        return lista;
    p->info = info;
    if (lista == NULL)
        p->prox = NULL;
    else
        p->prox = lista;
    lista = p;

    return lista;
}

No* linkedList_inserirNoFim(No *lista, INFO info)
{
    No *novoNo, *p = lista;

    novoNo = (No*) malloc(sizeof *p);
    if (novoNo == NULL) return lista;
    
    novoNo->info = info;
    novoNo->prox = NULL;
    if (lista == NULL)
        lista = novoNo;
    else
    {
        // p percorre a lista até apontar para o último nó
        while (p->prox != NULL)
            p = p->prox;
        p->prox = novoNo;
    }

    return lista;
}

