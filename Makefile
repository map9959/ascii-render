render: main.c
	gcc -o render vec3.c main.c -lm

run: render
	./render

clean:
	rm render