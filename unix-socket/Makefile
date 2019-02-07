all: client.opt server.opt

client.opt: client.ml
	ocamlfind ocamlopt -linkpkg -package unix -o client.opt client.ml

server.opt: server.ml
	ocamlfind ocamlopt -linkpkg -package unix -o server.opt server.ml
