all: probe test_animation.cmo

test_animation.cmo: animation.cma test_animation.ml
	ocamlc -c animation.cma test_animation.ml

animation.cma: animation.cmo
	ocamlc -a -o animation.cma animation.cmo

animation.cmo: animation.ml
	ocamlc -c animation.ml

probe: animation.cma main.ml
	ocamlfind ocamlc -o probe -linkpkg -package dynlink animation.cma main.ml

# ------------------------------

probe.opt: animation.cmx main.ml
	ocamlfind ocamlopt -o probe.opt -linkpkg -package dynlink animation.cmx main.ml

animation.cmx: animation.ml
	ocamlopt -c animation.ml

test_animation.cmxs: animation.cmx test_animation.ml
	ocamlopt -o test_animation.cmxs -c animation.cmx test_animation.ml
