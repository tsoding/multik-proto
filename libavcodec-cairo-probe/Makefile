LIBS=cairo sdl2 libavcodec

hello.png: avcodec-probe
	./avcodec-probe

avcodec-probe: main.c
	gcc -Wall -Werror $(shell pkg-config --cflags $(LIBS)) \
		-o avcodec-probe main.c \
		$(shell pkg-config --libs $(LIBS))
