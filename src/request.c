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

void init_header_list(struct header_list *hl)
{
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
