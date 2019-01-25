LIBS=cairo sdl2 libavcodec

hello.mpg: avcodec-probe
	./avcodec-probe hello.mpg mpeg1video

avcodec-probe: main.c
	gcc -Wall -Werror $(shell pkg-config --cflags $(LIBS)) \
		-o avcodec-probe main.c \
		$(shell pkg-config --libs $(LIBS))
