all: probe test_animation.cmo

test_animation.cmo: animation.cma test_animation.ml
	ocamlc -c animation.cma test_animation.ml

animation.cma: animation.cmo
	ocamlc -a -o animation.cma animation.cmo

animation.cmo: animation.ml
	ocamlc -c animation.ml

probe: animation.cma main.ml
	ocamlfind ocamlc -o probe -linkpkg -package dynlink animation.cma main.ml
