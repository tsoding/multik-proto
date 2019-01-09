open Animation

let rec eventLoop (n: int) =
  let module A = (val Animation.get_ca() : Anim) in
  A.render_frame ();
  if n > 10
  then
    begin
      Dynlink.loadfile("./test_animation.cmo");
      print_endline "Reloaded";
      eventLoop 0
    end
  else
    eventLoop (n + 1)

let _ =
  Dynlink.loadfile("./test_animation.cmo");
  eventLoop 0
