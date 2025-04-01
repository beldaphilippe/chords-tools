CFLAGS= -Wall -Wextra -fsanitize=address

main: src/*
	mkdir -p build
	gcc src/get_chord.c -Iinclude -o build/get_chord $(CFLAGS)

run:
	./build/get_chord

clean:
	rm -r build
