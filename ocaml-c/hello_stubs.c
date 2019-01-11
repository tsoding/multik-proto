#include <stdio.h>
#include <caml/mlvalues.h>

CAMLprim value
caml_print_hello(value unit)
{
    printf("Hello\n");
    return Val_unit;
}
