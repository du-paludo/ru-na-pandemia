#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "libpilha.h"
#include "libfila.h"
#include "liblista.h"

#define num_pessoas 1000

typedef struct
{
    int ticket; /* Identifica cada pessoa com um inteiro positivo não-repetido */
    int vacinado; /* 0 - não vacinado (10%), 1 - vacinado (90%) */
    int mascara; /* 0 - sem máscara (20%), 1 - com máscara (80%)*/
    double dinheiro; /* 1.30 (60%) ou 3.80 (40%) */
    int cod_atendimento;
    /* 0 - foi atendido
	1 - não foi atendido por não estar vacinado
	2 - não foi atendido por não ter dinheiro para comprar máscara
	3 - não foi atendido por faltar máscara
	4 - não foi atendido por faltar refeição */
} pessoa_t;

typedef struct
{
	float dinheiro_total; /* Armazena o dinheiro total arrecadado no dia */
	float dinheiro_refeicoes; /* Armazena o dinheiro arrecadado com refeições */
	float dinheiro_mascaras; /* Armazena o dinheiro arrecadado com máscaras */
	int qtde_tickets; /* Armazena a quantidade de tickets não utilizados */
} contabilidade_t;

/* Retorna um valor aleatório entre n e m */
int aleat (int n, int m)
{
	return ((rand()%(m - n + 1)) + n);
}

/* Cria uma pilha de tamanho n e a preenche com 1 */
pilha_t* gera_pilha_cheia (int n)
{
	pilha_t* aux = pilha_cria(n);
	int i;
	for (i = 0; i < n; i++)
		push(aux, 1);
	return aux;
}

/* Cria um vetor de pessoas alocado dinamicamente e aleatoriza atributos */
pessoa_t* gera_pessoas ()
{
	pessoa_t* aux = malloc(sizeof(pessoa_t) * num_pessoas);
	int i;

	for (i = 0; i < num_pessoas; i++)
	{
		(aux+i)->ticket = i+1;

		if (aleat(1,10) <= 9)
			(aux+i)->vacinado = 1;
		else
			(aux+i)->vacinado = 0;

		if (aleat(1,10) <= 8)
			(aux+i)->mascara = 1;
		else
			(aux+i)->mascara = 0;

		if (aleat(1,10) <= 6)
			(aux+i)->dinheiro = 1.30;
		else
			(aux+i)->dinheiro = 3.80;
	}
	return aux;
}

/* Aloca memória para a contabilidade e a inicializa */
contabilidade_t* inicializa_contabilidade ()
{
	contabilidade_t* aux = malloc(sizeof(contabilidade_t));
	aux->dinheiro_total = 0;
	aux->dinheiro_refeicoes = 0;
	aux->dinheiro_mascaras = 0;
	aux->qtde_tickets = 0;
	return aux;
}

/* Insere todos os tickets na fila de atendimento */
void insere_tickets (pessoa_t* conjunto, fila_t* fila_atendimentos)
{
	int i;
	for (i = 0; i < num_pessoas; i++)
		queue(fila_atendimentos, (conjunto+i)->ticket);
}

/* Imprime as informações de contabilidade */
void imprime_contabilidade (pessoa_t* conjunto, lista_t* lista_nao_atendidos, contabilidade_t* contabilidade)
{
	contabilidade->dinheiro_total = contabilidade->dinheiro_mascaras + contabilidade->dinheiro_refeicoes;
	pessoa_t* pessoa;
	int ticket;

	printf("Números dos tickets não atendidos: ");
	lista_imprime(lista_nao_atendidos);

	while (!lista_vazia(lista_nao_atendidos))
	{
		lista_retira_inicio(lista_nao_atendidos, &ticket);
		pessoa = (conjunto + ticket - 1);
		switch (pessoa->cod_atendimento)
		{
			case 1:
				printf("Ticket %d: não vacinado\n", pessoa->ticket);
				break;
			case 2:
				printf("Ticket %d: sem dinheiro suficiente para comprar máscara\n", pessoa->ticket);
				break;
			case 3:
				printf("Ticket %d: acabaram as máscaras\n", pessoa->ticket);
				break;
			case 4:
				printf("Ticket %d: acabaram as refeições\n", pessoa->ticket);
				break;
			default:
				break;
		}
	}

	printf("Dinheiro total arrecadado: %.2f\n", contabilidade->dinheiro_total);
	printf("Dinheiro das máscaras: %.2f\n", contabilidade->dinheiro_mascaras);
	printf("Dinheiro das refeições: %.2f\n", contabilidade->dinheiro_refeicoes);
	printf("Quantidade de tickets não atendidos: %d\n", contabilidade->qtde_tickets);
}

int main ()
{
	/* Gera uma seed aleatória */

	srand(time(0));

	/* Inicializa variáveis */

	int num_mascaras = aleat(1, 100);
	pilha_t* pilha_mascaras = gera_pilha_cheia(num_mascaras);

	int num_refeicoes = aleat(500, 1000);
	pilha_t* pilha_refeicoes = gera_pilha_cheia(num_refeicoes);

	pessoa_t* conjunto = gera_pessoas();

	fila_t* fila_atendimentos = fila_cria();
	lista_t* lista_nao_atendidos = lista_cria();

	insere_tickets(conjunto, fila_atendimentos);
	contabilidade_t* contabilidade = inicializa_contabilidade();

	pessoa_t* pessoa;
	int ticket;

	/* Fiscal do RU */

	while (!fila_vazia(fila_atendimentos))
	{
		/* 	Remove a pessoa da fila e atribui seu índice no conjunto à variável pessoa */
		dequeue(fila_atendimentos, &ticket);
		pessoa = (conjunto + ticket - 1);

		/* Se a pilha de refeições estiver vazia, a pessoa não é atendida */
		if (pilha_vazia(pilha_refeicoes))
		{
			lista_insere_ordenado(lista_nao_atendidos, pessoa->ticket);
			pessoa->cod_atendimento = 4;
			contabilidade->qtde_tickets++;
		}
		else
		{
			if (pessoa->vacinado)
			{
				/* Se a pessoa está vacinada e de máscara, é atendida */
				if (pessoa->mascara)
				{
					pessoa->dinheiro -= 1.30;
					contabilidade->dinheiro_refeicoes += 1.30;
					pop(pilha_refeicoes);
					pessoa->cod_atendimento = 0;
				}

				/* Caso contrário, testa se tem máscaras disponíveis para compra */
				else
				{
					if (!pilha_vazia(pilha_mascaras))
					{
						/* Se tiver dinheiro suficiente, a pessoa compra a máscara e é reinserida na fila */
						if (pessoa->dinheiro == 3.8)
						{
							pessoa->dinheiro -= 2.5;
							contabilidade->dinheiro_mascaras += 2.5;
							pop(pilha_mascaras);
							pessoa->mascara = 1;
							queue(fila_atendimentos, pessoa->ticket);
						}

						/* Caso contrário, a pessoa não é atendida */
						else
						{
							lista_insere_ordenado(lista_nao_atendidos, pessoa->ticket);
							pessoa->cod_atendimento = 2;
							contabilidade->qtde_tickets++;
						}
					}

					/* Se a pilha de máscaras estiver vazia, a pessoa não é atendida */
					else
					{
						lista_insere_ordenado(lista_nao_atendidos, pessoa->ticket);
						pessoa->cod_atendimento = 3;
						contabilidade->qtde_tickets++;
					}
				}
			}

			/* Se a pessoa não estiver vacinada, não é atendida */
			else
			{
				lista_insere_ordenado(lista_nao_atendidos, pessoa->ticket);
				pessoa->cod_atendimento = 1;
				contabilidade->qtde_tickets++;
			}
		}
	}

	/* Imprime os dados de contabilidade */

	imprime_contabilidade(conjunto, lista_nao_atendidos, contabilidade);

	/* Libera a memória alocada */

	free(conjunto);
	free(contabilidade);
	pilha_destroi(pilha_mascaras);
	pilha_destroi(pilha_refeicoes);
	fila_destroi(fila_atendimentos);
	lista_destroi(lista_nao_atendidos);

	return 0;
}