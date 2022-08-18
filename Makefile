parametrosCompilacao=-Wall -std=c99
nomePrograma=ru_na_pandemia

all: ru_na_pandemia

ru_na_pandemia: ru_na_pandemia.o libpilha.o libfila.o liblista.o
	gcc -o ru_na_pandemia ru_na_pandemia.o libpilha.o libfila.o liblista.o $(parametrosCompilacao)

ru_na_pandemia.o: ru_na_pandemia.c
	gcc -c ru_na_pandemia.c $(parametrosCompilacao)

libpilha.o: libpilha.h libpilha.c
	gcc -c libpilha.c $(parametrosCompilacao)

libfila.o: libfila.h libfila.c
	gcc -c libfila.c $(parametrosCompilacao)

liblista.o: liblista.h liblista.c
	gcc -c liblista.c $(parametrosCompilacao)

clean:
	rm -f *.o *.gch $(nomePrograma)

