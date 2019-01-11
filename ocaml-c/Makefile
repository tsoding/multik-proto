hello: hello_stubs.c hello.ml
	ocamlc -o hello.opt hello.ml hello_stubs.c

hello.opt: hello_stubs.c hello.ml
	ocamlopt -o hello.opt hello.ml hello_stubs.c
