#include <stdio.h>
#include <stdlib.h>
#include "libfila.h"

fila_t* fila_cria ()
{
    fila_t* f = malloc(sizeof(fila_t));
    if (f == NULL)
        return NULL;
    f->ini = NULL;
    f->fim = NULL;
    f->tamanho = 0;
    return f;
}

fila_t* fila_destroi (fila_t* f)
{
    nodo_f_t* atual = f->ini;
    nodo_f_t* aux;

    /* Percorre a lista até o fim ser nulo,
    limpando o nodo atual e armazenando em uma variável o próximo */
    while (atual != NULL)
    {
        aux = atual->prox;
        free(atual);
        atual = aux;
    }
    free(f);
    return NULL;
}

int fila_vazia (fila_t* f)
{
    if (f->ini == NULL)
        return 1;
    return 0;
}

int fila_tamanho (fila_t* f)
{
    return f->tamanho;
}

int queue (fila_t* f, int elemento)
{
    /* Aloca memória para um novo nodo */
    nodo_f_t* aux = malloc(sizeof(nodo_f_t));
    if (aux == NULL)
        return 0;

    /* Inicializa o nodo e incrementa o tamanho da fila */
    aux->chave = elemento;
    aux->prox = NULL;
    f->tamanho++;

    /* Se a fila estiver vazia, então o novo nodo é tanto o início como o fim da fila */
    if (fila_vazia(f))
    {
        f->fim = aux;
        f->ini = f->fim;
    }

    /* Se não, aponta o fim da fila para o novo nodo */
    else
    {
        f->fim->prox = aux;
        f->fim = aux;
    }
    return 1; 
}

int dequeue (fila_t* f, int* elemento)
{
    /* Se a fila estiver vazia, retorna 0 */
    if (fila_vazia(f))
        return 0;

    /* Retorna o elemento a ser removido */
    *elemento = f->ini->chave;

    /* Armazena o início da fila em uma variável auxiliar */
    nodo_f_t* aux = f->ini;

    /* Aponta o início para o próximo elemento da fila */
    f->ini = f->ini->prox;

    /* Se o novo início for nulo, então o fim também deve ser */
    if (f->ini == NULL)
        f->fim = NULL;

    /* Remove o primeiro elemento */
    free(aux);
    f->tamanho--;
    return 1;
}

void fila_imprime (fila_t* f)
{
    if (fila_vazia(f))
        return;

    /* Atribui o início da fila a uma variável de controle */
    nodo_f_t* aux = f->ini;

    /* Imprime cada elemento da fila até atingir o final */
    while (aux->prox != NULL)
    {
        printf("%d ", aux->chave);
        aux = aux->prox;
    }
    printf("%d\n", aux->chave);
}