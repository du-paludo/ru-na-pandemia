#include <stdio.h>
#include <stdlib.h>
#include "liblista.h"

lista_t* lista_cria ()
{
    /* Aloca memória dinamicamente */
    lista_t* l = malloc(sizeof(lista_t));
    if (l == NULL)
        return NULL;

    /* Inicializa a lista com início vazio e tamanho nulo */
    l->ini = NULL;
    l->tamanho = 0;
    return l;
}

lista_t* lista_destroi (lista_t* l)
{
    nodo_l_t* atual = l->ini;
    nodo_l_t* aux;

    /* Percorre a lista, limpando o nodo atual e armazenando em uma variável o próximo */
    while (atual != NULL)
    {
        aux = atual->prox;
        free(atual);
        atual = aux;
    }
    free(l);
    return NULL;
}

int lista_vazia (lista_t* l)
{
    if (l->ini == NULL)
        return 1;
    return 0;
}

int lista_tamanho (lista_t* l)
{
    return l->tamanho;
}

int lista_insere_inicio (lista_t* l, int elemento)
{
    /* Aloca memória para um nodo novo */
    nodo_l_t* nodo = malloc(sizeof(nodo_l_t));
    if (nodo == NULL)
        return 0;
    nodo->elemento = elemento;
    l->tamanho++;
    nodo->prox = l->ini;
    l->ini = nodo;
    return 1;
}

int lista_insere_fim (lista_t* l, int elemento)
{
    /* Se a lista estiver vazia, insere no início */
    if (lista_vazia(l))
        return lista_insere_inicio(l, elemento);

    /* Se não, inicializa o novo nodo */
    nodo_l_t* nodo = malloc(sizeof(nodo_l_t));
    if (nodo == NULL)
        return 0;
    nodo->elemento = elemento;
    l->tamanho++;

    /* Percorre a lista até chegar no final */
    nodo_l_t* anterior;
    nodo_l_t* atual = l->ini;
    while (atual != NULL)
    {
        anterior = atual;
        atual = atual->prox;
    }
    anterior->prox = nodo;
    atual = nodo;
    nodo->prox = NULL;
    return 1;
}

int lista_insere_ordenado (lista_t* l, int elemento)
{
    /* Se a lista estiver vazia ou o elemento for menor que o primeiro, insere no início */
    if ((lista_vazia(l)) || (elemento <= l->ini->elemento))
        return lista_insere_inicio(l, elemento);

    nodo_l_t* nodo = malloc(sizeof(nodo_l_t));
    if (nodo == NULL)
        return 0;
    nodo->elemento = elemento;
    l->tamanho++;

    /* Percorre a lista até chegar no fim ou encontrar
    um elemento maior que aquele a ser inserido */
    nodo_l_t* aux = l->ini;
    while ((aux->prox != NULL) && (elemento > aux->prox->elemento))
        aux = aux->prox;
    nodo->prox = aux->prox;
    aux->prox = nodo;
    return 1;
}

int lista_retira_inicio (lista_t* l, int* elemento)
{
    /* Retorna 0 se a lista estiver vazia */
    if (lista_vazia(l))
        return 0;

    /* Guarda o primeiro elemento na variável elemento */
    *elemento = l->ini->elemento;

    /* Armazena o segundo nodo da lista em uma variável auxiliar */
    nodo_l_t* aux = l->ini->prox;

    /* Remove o primeiro nodo */
    free(l->ini);
    l->tamanho--;

    /* Início da fila aponta para o segundo nodo */
    l->ini = aux;
    return 1;
}

int lista_retira_fim (lista_t* l, int* elemento)
{
    /* Se a lista estiver vazia, retorna 0 */
    if (lista_vazia(l))
        return 0;

    /* Se a lista possuir apenas um elemento, ele é o início da lista */
    if (l->tamanho == 1)
        return lista_retira_inicio(l, elemento);

    /* Percorre a lista até encontrar o último elemento e o remove */
    nodo_l_t* anterior;
    nodo_l_t* atual = l->ini;
    while (atual->prox != NULL)
    {
        anterior = atual;
        atual = atual->prox;
    }
    anterior->prox = NULL;
    *elemento = atual->elemento;
    free(atual);
    l->tamanho--;
    return 1;
}

int lista_retira_elemento (lista_t *l, int* elemento)
{
    if (lista_vazia(l))
        return 0;

    /* Testa se o elemento a ser removido é o primeiro */
    if (l->ini->elemento == *elemento)
        return lista_retira_inicio(l, elemento);

    /* Percorre toda a lista até encontrar o elemento, armazenando o ponteiro do
    nodo anterior e do atual */
    nodo_l_t* anterior = l->ini;
    nodo_l_t* atual = anterior->prox;
    while (atual != NULL)
    {
        if (atual->elemento == *elemento)
        {
            anterior->prox = atual->prox;
            free(atual);
            l->tamanho--;
            return 1;
        }
        anterior = atual;
        atual = atual->prox;
    }
    return 0;

}

int lista_pertence (lista_t* l, int elemento)
{
    nodo_l_t* aux = l->ini;

    /* Verifica todos os elementos da lista até encontrar o elemento */
    while (aux != NULL)
    {
        if (aux->elemento == elemento)
            return 1;
        aux = aux->prox;
    }
    return 0;
}

void lista_imprime (lista_t* l)
{
    if (lista_vazia(l))
        return;

    /* Atribui o início da lista a uma variável de controle */
    nodo_l_t* aux = l->ini;

    /* Imprime cada elemento da lista até atingir o final */
    while (aux->prox != NULL)
    {
        printf("%d ", aux->elemento);
        aux = aux->prox;
    }
    printf("%d\n", aux->elemento);
}