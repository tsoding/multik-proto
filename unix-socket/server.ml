let _ =
  Unix.establish_server
    (fun inc outc ->
      let x : string = input_value inc in
      output_value outc ("Server Response: " ^ x))
    (Unix.ADDR_UNIX "khooy")
