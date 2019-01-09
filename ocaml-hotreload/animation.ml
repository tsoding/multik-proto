module type Anim =
  sig
    val render_frame: unit -> unit
  end

let ca : (module Anim) option ref = ref None
let get_ca ()  =
  match !ca with
  | Some a -> a
  | None -> failwith "No animation loaded"
