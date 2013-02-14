#ifndef _TINYSCGI_REQUEST_H
#define _TINYSCGI_REQUEST_H

#include "string.h"

struct range
{
    int begin;
    int end;
};

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

#endif
