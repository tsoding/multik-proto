let _ =
  let (inc, outc) =
    Unix.open_connection (Unix.ADDR_UNIX "khooy")
  in output_value outc "VI VON ZULUL";
     flush outc;
     inc |> input_value |> print_endline
