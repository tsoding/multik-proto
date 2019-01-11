hello: hello.cmo dllhello_stubs.so
	ocamlc -o hello hello.cmo -dllib dllhello_stubs.so

hello.cmo: hello.ml
	ocamlc -c  hello.ml

dllhello_stubs.so: hello_stubs.o
	ocamlmklib -o hello_stubs hello_stubs.o

hello_stubs.o: hello_stubs.c
	ocamlc -c hello_stubs.c
