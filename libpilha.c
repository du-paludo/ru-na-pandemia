#include <stdio.h>
#include <stdlib.h>
#include "libpilha.h"

pilha_t* pilha_cria (int nelem)
{
	/* Aloca memória dinamicamente para a pilha e o vetor de elementos */
	pilha_t* pilha = malloc(sizeof(pilha_t));
	if (pilha == NULL)
		return NULL;
	pilha->elems = malloc(sizeof(int) * nelem);
	if (pilha->elems == NULL)
		return NULL;

	pilha->topo = -1;
	pilha->nelem = nelem;
	return pilha;
}

int push (pilha_t* pilha, int elem)
{
	/* Retorna -1 se a pilha estiver cheia */
	if (pilha->topo == pilha->nelem-1)
		return -1;

	/* Caso contrário, incrementa o topo, atribui um elemento
	e retorna o número de elementos na pilha */
	pilha->topo++;
	pilha->elems[pilha->topo] = elem;
	return pilha_tamanho(pilha);
}

int pop (pilha_t* pilha)
{
	/* Retorna 0 se a pilha estiver vazia */
	if (pilha_vazia(pilha))
		return 0;
	
	/* Caso contrário, decrementa o topo e retorna o elemento removido */
	pilha->topo--;
	return pilha->elems[pilha->topo+1];
}

int pilha_topo (pilha_t* pilha)
{
	return pilha->elems[pilha->topo];
}

int pilha_tamanho (pilha_t* pilha)
{
	return pilha->topo+1;
}

int pilha_vazia (pilha_t* pilha)
{
	if (pilha->topo == -1)
		return 1;
	return 0;
}

pilha_t* pilha_destroi (pilha_t* pilha)
{
	/* Libera a memória alocada dinamicamente */
	free(pilha->elems);
	free(pilha);
	return NULL;
}

void pilha_imprime (pilha_t* pilha)
{
	if (pilha_vazia(pilha))
		return;
	int i;
	for (i = 0; i <= pilha->topo-1; i++)
		printf("%d ", pilha->elems[i]);
	printf("%d\n", pilha->elems[pilha->topo]);
}