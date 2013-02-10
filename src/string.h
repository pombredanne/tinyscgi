#ifndef _TINYSCGI_STRING_H
#define _TINYSCGI_STRING_H

#define STRING_RESIZE_STEP (255)

struct string
{
    int length;
    char *value;
};

#endif
