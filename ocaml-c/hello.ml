external print_hello: unit -> unit = "caml_print_hello"

let () =
  print_hello ();
  print_endline "Ran from OCaml"
