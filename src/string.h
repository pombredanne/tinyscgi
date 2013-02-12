#ifndef _TINYSCGI_STRING_H
#define _TINYSCGI_STRING_H

#define STRING_RESIZE_STEP (255)

struct string
{
    int length;
    char *value;
};

extern void init_string(struct string *);
extern void resize_string(struct string *);
extern void clean_string(struct string *);

#endif
