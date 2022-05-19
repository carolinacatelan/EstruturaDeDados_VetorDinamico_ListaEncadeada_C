#include "arrayList.h"

INFO *array_adicionarNoFim(INFO v[], int *v_length, INFO info)
{
    int n = *v_length;

    if (v == NULL || n == 0) 
        v = (INFO *)malloc(sizeof *v);
    else
        v = (INFO *)realloc(v, (n + 1) * sizeof *v);
    if (v == NULL)
    {
        *v_length = 0;
        return NULL;
    }
    v[n] = info;
    (*v_length)++;

    return v;
}

INFO *array_removerElemento(INFO v[], int *v_length, int index)
{
    int n = *v_length, i;
    INFO *p;

    if (index < 0 || index > n)
        return v;

    if (index == 0)
    {
        p = &v[0];
        v = &v[1];
        free(p);
    }
    else
    {
        for (i = index; i < n - 1; i++)
            v[i] = v[i + 1];
        p = &v[n - 1];
        free(p);
    }
    (*v_length)--;

    return v;
}

INFO *array_limpar(INFO v[], int *v_length)
{
    free(v);
    v = NULL;
    *v_length = 0;

    return v;
}