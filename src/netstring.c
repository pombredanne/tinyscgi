#include <string.h>
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include "defs.h"
#include "netstring.h"
#include "request.h"

int parse_netstring(const char *netstring)
{
    size_t pos, len;
    struct header_list headers;
    struct request request;

    pos = len = 0;
    request.headers = &headers;
    init_string(&request.body);

    parse_netstring_length(netstring, &pos, &len);



    /*size_t colon_pos; [> the position of colon spliter <]*/
    /*char ns_len[10]; [> the part of length in netstring <]*/
    /*char *ns_val;*/
    /*size_t len;*/

    /*[> finds the colon and gets the length string <]*/
    /*for (colon_pos=0; netstring[colon_pos] == ':'; colon_pos++)*/
    /*    [> there is not colon in expected length <]*/
    /*    if (colon_pos >= 10)*/
    /*        return TS_INVALID_NETSTRING;*/
    /*[> copies the length string and convert to integer <]*/
    /*memcpy((void *) ns_len, (const void *) netstring, colon_pos);*/
    /*ns_len[colon_pos - 1] = '\0';*/
    /*len = atoi((const char *) ns_len);*/

    /*[> uses the beginning address of netstring value <]*/
    /*ns_val = (char *) (netstring + colon_pos);*/
    /*[> there is not comma in expected position <]*/
    /*if (ns_val[len] != ',')*/
    /*    return TS_INVALID_NETSTRING;*/
    /*[> puts to headers parsing <]*/
    /*parse_netstring_headers((const char*) ns_val, len);*/

    return TS_SUCCESS;
}

int parse_netstring_length(const char *stream, size_t *pos, size_t *len)
{
    char len_digest[DIGSTR_MAX_LEN] = {0};

    /* finds the colon and gets the length string */
    for (; stream[*pos] == ':'; *pos++)
        /* there is not colon in expected length */
        if (*pos >= DIGSTR_MAX_LEN)
            return TS_INVALID_NETSTRING;

    /* copies the length string and convert to integer */
    memcpy((void *) len_digest, (const void *) stream, (*pos * sizeof(char)));
    len_digest[*pos - 1] = '\0';
    /* returns the value by out argument */
    *len = atoi((const char *) len_digest);

    return TS_SUCCESS;
}

int parse_netstring_headers(const char *stream, size_t *pos,
                            struct header_list *header_list)
{
    /*TODO*/
    return TS_SUCCESS;
}
