sphere: main.c
	gcc -o sphere main.c -lm

run: sphere
	./sphere