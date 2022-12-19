CFLAGS := -g -std=c99 -Wall -Wformat=2
CFLAGS += -Wunreachable-code
CFLAGS += -Wconversion -Wno-sign-conversion -Wbad-function-cast
CFLAGS += -Werror

VFLAGS = --leak-check=full --track-origins=yes --show-reachable=yes

OBJMAIN1 = counting_filters.o hash.o heap.o strutil.o  
OBJMAIN2 = hash.o cola.o strutil.o 


all: $(OBJMAIN1) $(OBJMAIN2)
	gcc $(CFLAGS) -o procesar_tweets $(OBJMAIN1)  procesar_tweets.c 
	gcc $(CFLAGS) -o procesar_usuarios $(OBJMAIN2)  procesar_usuario.c 
	rm *.o

cola.o:
	gcc $(CFLAGS) cola.c -c	

heap.o:  
	gcc $(CFLAGS) heap.c  -c

hash.o: 
	gcc $(CFLAGS) hash.c -c	

counting_filters.o:
	gcc $(CFLAGS) counting_filters.c -c

strutil.o:
	gcc $(CFLAGS) strutil.c -c	

clean:
	rm procesar_tweets procesar_usuarios 

run:
	cat tweets.txt | valgrind $(VFLAGS) ./procesar_tweets 5000000 10
	valgrind $(VFLAGS) ./procesar_usuarios tweets.txt
	
	#cat tweets_head.txt | valgrind $(VFLAGS) ./procesar_tweets 25 10
	#valgrind $(VFLAGS) ./procesar_usuarios tweets_head.txt
	#./procesar_usuarios tweets.txt
	#rm procesar_usuarios procesar_tweets












