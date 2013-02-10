#include <stdlib.h>
#include <string.h>
#include "string.h"

void init_string(struct string *s)
{
    s->length = 0;
    s->value = (char *) malloc(STRING_RESIZE_STEP);
    memset(s->value, 0, STRING_RESIZE_STEP);
}

/* calculate new length of string and reallocate memory. */
void resize_string(struct string *s)
{
    int n_step;
    n_step = (s->length / (int) STRING_RESIZE_STEP) + 1;
    s->value = realloc(s->value, (size_t) (n_step * STRING_RESIZE_STEP));
}

void clean_string(const struct string *str)
{
    free(str->value);
}
