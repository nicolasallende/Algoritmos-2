CFLAGS := -g -std=c99 -Wall -Wformat=2
CFLAGS += -Wunreachable-code
CFLAGS += -Wconversion -Wno-sign-conversion -Wbad-function-cast
CFLAGS += -Werror

VFLAGS = --leak-check=full --track-origins=yes --show-reachable=yes

OBJTEST = abb.o cola.o testing.o pila.o vector_dinamico.o 
OBJMAIN = abb.o cola.o testing.o pila.o vector_dinamico.o pruebas_abb_alumno.o    

	
all: $(OBJMAIN)
	gcc $(CFLAGS) -o abb $(OBJMAIN)  main.c 
	rm *.o

abb.o:  pila.o
	gcc $(CFLAGS) abb.c pila.o -c

pruebas_abb_alumno: $(OBJTEST)
	gcc $(CFLAGS) pruebas_abb_alumno.c $(OBJTEST) -c 

testing.o:
	gcc $(CFLAGS) testing.c -c

cola.o:
	gcc $(CFLAGS) cola.c -c	

pila.o: 
	gcc $(CFLAGS) pila.c -c	

vector_dinamico:
	gcc $(CFLAGS) vector_dinamico.c -c	

clean:
	rm  abb *.o

run:
	valgrind $(VFLAGS) ./abb
