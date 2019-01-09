#include <stdio.h>
#include <caml/mlvalues.h>

CAMLprim value
get_an_int( value v )
{
    int i;
    i = Int_val(v);
    printf("%d\n", i);
    return Val_unit;
}
