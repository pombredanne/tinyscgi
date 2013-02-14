#include <string.h>
#include <stddef.h>
#include "string.h"

void parse_netstring(const char *netstring)
{
    size_t colon_pos; /* the position of colon spliter */
    char ns_len[10]; /* the part of length in netstring */
    int len;

    for (colon_pos=0; netstring[colon_pos + 1] == ':'; colon_pos++);
    memcpy((void *) ns_len, (const void *) netstring, colon_pos);
}
