# RU Fiscal Simulation

This project simulates a queue management system for a university restaurant (RU). It handles the distribution of meals and masks to people, while keeping track of the total money collected and the number of people not attended due to various reasons.

## Files

- `main.c`: Contains the main logic for the simulation.
- `libpilha.h` and `libpilha.c`: Stack implementation used for managing masks and meals.
- `libfila.h` and `libfila.c`: Queue implementation used for managing the queue of people.
- `liblista.h` and `liblista.c`: List implementation used for managing the list of people not attended.

## Structures

### `pessoa_t`

Represents a person in the simulation.

- `ticket`: Unique identifier for each person.
- `vacinado`: Vaccination status (0 - not vaccinated, 1 - vaccinated).
- `mascara`: Mask status (0 - no mask, 1 - has mask).
- `dinheiro`: Amount of money the person has (1.30 or 3.80).
- `cod_atendimento`: Code indicating the reason for not being attended (0 - attended, 1 - not vaccinated, 2 - insufficient money for mask, 3 - masks out of stock, 4 - meals out of stock).

### `contabilidade_t`

Keeps track of the financial data.

- `dinheiro_total`: Total money collected.
- `dinheiro_refeicoes`: Money collected from meals.
- `dinheiro_mascaras`: Money collected from masks.
- `qtde_tickets`: Number of tickets not used.

## Functions

`aleat(int n, int m)`

Returns a random value between `n` and `m`.

`gera_pilha_cheia(int n)`

Creates a stack of size `n` and fills it with the value `1`.

`gera_pessoas()`

Creates an array of `pessoa_t` and randomizes their attributes.

`inicializa_contabilidade()`

Allocates memory for the `contabilidade_t` structure and initializes it.

`insere_tickets(pessoa_t* conjunto, fila_t* fila_atendimentos)`

Inserts all tickets into the queue of attendances.

`imprime_contabilidade(pessoa_t* conjunto, lista_t* lista_nao_atendidos, contabilidade_t* contabilidade)`

Prints the financial data and the list of people not attended.

## Simulation Workflow

1. **Initialization:**
   - Set up a random seed.
   - Generate random numbers of masks and meals.
   - Initialize the stack of masks and meals.
   - Generate the array of people.
   - Initialize the queue of attendances and the list of people not attended.
   - Insert tickets into the queue.
   - Initialize the financial data structure.

2. **Processing:**
   - Process each person in the queue.
   - Check if meals are available.
   - Check vaccination and mask status.
   - Handle financial transactions.
   - Record the reasons for not being attended.

3. **Output:**
   - Print the financial data.
   - Print the list of people not attended and the reasons.

4. **Cleanup:**
   - Free allocated memory for all data structures.

## Compilation and Execution

### Compilation

Compile the project using `make`.

### Execution
Run the compiled program using `./ru_fiscal`.

## Output

The program outputs the list of people not attended with reasons, the total money collected, the money collected from meals and masks, and the number of tickets not used.
