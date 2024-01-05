sphere: main.c
	gcc -o sphere vec3.c main.c -lm

run: sphere
	./sphere

clean:
	rm sphere