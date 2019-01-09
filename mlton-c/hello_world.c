#include <stdio.h>
#include "export.h"

Int32 say_hello(Int32 n, Pointer name)
{
    printf("Hello %s!\n", (unsigned char*) name);
    return n;
}
