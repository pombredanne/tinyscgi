#ifndef _TINYSCGI_NETSTRING_H
#define _TINYSCGI_NETSTRING_H

#include <stddef.h>
#include "request.h"

int parse_netstring(const char *);
int parse_netstring_headers(const char *, size_t *, struct header_list *);
int parse_netstring_length(const char *, size_t *, size_t *);

#endif
