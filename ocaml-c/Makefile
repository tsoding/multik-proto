all: hello.opt

hello.opt: hello.cmx hello_stubs.o
	ocamlopt -o hello.opt hello_stubs.o hello.cmx -ccopt "$(shell pkg-config --cflags --libs sdl2 cairo)" 

hello.cmx: hello.ml
	ocamlopt -c hello.ml -ccopt "$(shell pkg-config --cflags --libs sdl2 cairo)"

hello_stubs.o: hello_stubs.c
	ocamlopt -c hello_stubs.c -ccopt "$(shell pkg-config --cflags --libs sdl2 cairo)"
