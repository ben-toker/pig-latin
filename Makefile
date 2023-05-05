all: pig.c
	gcc -o pig pig.c

pig: pig.c
	gcc -o pig pig.c

clean: 
	rm pig

