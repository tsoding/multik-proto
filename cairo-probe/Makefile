hello.png: cairo-probe
	./cairo-probe

cairo-probe: main.c
	gcc -Wall -Werror $(shell pkg-config --cflags cairo) \
		-o cairo-probe main.c \
		$(shell pkg-config --libs cairo)
