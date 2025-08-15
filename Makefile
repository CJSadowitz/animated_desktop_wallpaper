HEADERS = src/shaders.h
CFLAGS  = -Wall -Isrc -g
LDFLAGS = -lglfw -lGL -ldl

default: main

main: main.c src/glad.c $(HEADERS)
	gcc ${CFLAGS} main.c src/glad.c -o output ${LDFLAGS}

clean:
	rm -f output

