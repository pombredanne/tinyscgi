#include <stddef.h>
#include <stdlib.h>
#include "request.h"
#include "string.h"

void init_header(struct header *h)
{
    init_string(&h->name);
    init_string(&h->value);
}

void clean_header(struct header *h)
{
    clean_string(&h->name);
    clean_string(&h->value);
}

void init_header_list(struct header_list *hl, struct header *h)
{
    hl->item = *h;
    hl->next = NULL;
}

void append_header_list(struct header_list *hl, struct header *h)
{
    while (hl->next)
        hl = &hl->next;
    init_header_list(&hl->next, h);
}

void clean_header_list(struct header_list *hl)
{
}

void init_request(struct request *r)
{
}

void clean_request(struct request *r)
{
}
