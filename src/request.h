#ifndef _TINYSCGI_REQUEST_H
#define _TINYSCGI_REQUEST_H

#include "string.h"

struct header
{
    struct string name;
    struct string value;
};

struct header_list
{
    struct header *item;
    struct header_list *next;
};

struct request
{
    struct header_list *headers;
    struct string body;
};

extern void init_header(struct header *);
extern void clean_header(struct header *);
extern void init_header_list(struct header_list *);
extern void clean_header_list(struct header_list *);
extern void init_request(struct request *);
extern void clean_request(struct request *);

#endif
