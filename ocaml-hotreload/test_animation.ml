open Animation

module TestAnim: Anim =
  struct
    let render_frame () = print_endline "Hello"
  end

let () =
  ca := Some (module TestAnim : Anim)
