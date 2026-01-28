CC = gcc
CFLAGS = -O3

all: main_liste main_matrice

main_liste: main_liste.c prototypes.h
	$(CC) $(CFLAGS) main_liste.c -o main_liste 

main_matrice: main_matrice.c prototypes.h
	$(CC) $(CFLAGS) main_matrice.c -o main_matrice 

clean:
	rm -f main_liste main_matrice *.o
