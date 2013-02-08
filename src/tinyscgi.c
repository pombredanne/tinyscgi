#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define SCGI_HEADER_STRING_MAX_LEN (255)

struct header
{
    char name[SCGI_HEADER_STRING_MAX_LEN];
    char value[SCGI_HEADER_STRING_MAX_LEN];
    struct header *next;
};

struct range
{
    int begin;
    int end;
};

struct request
{
    struct header *first_header;
};

void parse_netstring_length(const char *netstring, struct range *range)
{
    char length_digest[10]; /* max length is prepared for 2^31 */
    int i;

    memset(length_digest, 0, 10);

    /* collect chars until meet spilter */
    for (i=0; i<10; i++)
    {
        if (netstring[i] == ':')
            break;
        length_digest[i] = netstring[1];
    }

    range->begin = i + 1; /* ignore spilter */
    range->end = range->begin + atoi((const char *)length_digest);

    assert(netstring[range->begin - 1] == ':');
    assert(netstring[range->end + 1] == ',');
}

struct header * init_header(struct header *prev)
{
    struct header *header;

    header = (struct header *) malloc(sizeof (struct header *));

    memset(header->name, 0, SCGI_HEADER_STRING_MAX_LEN);
    memset(header->value, 0, SCGI_HEADER_STRING_MAX_LEN);
    header->next = NULL;

    if (prev)
        prev->next = header;

    return header;
}

void clean_header(struct header *first)
{
    struct header *current, *prev;

    current = first;
    while (current) 
    {
        prev = current;
        current = current->next;
        free(prev);
    }
}

struct header * parse_netstring(const char *netstring)
{
    int i, j;
    int state; /* 0 for name, 1 for value */
    struct range range;
    struct header *first_header, *header;

    parse_netstring_length(netstring, &range);

    first_header = header = init_header(NULL);
    state = 0; /* default for name */

    for (i=range.begin, j=0; i<range.end; i++, j++)
    {
        if (netstring[i] == '\0')
        {
            state = !state; /* switch state */
            j = 0;

            /* state == name after switching, then it is a new header */
            if (state == 0)
                header = init_header(header);
        }

        /* copy string to target attribute */
        switch (state)
        {
            case 0:
                header->name[j] = netstring[i];
                break;
            case 1:
                header->value[j] = netstring[i];
                break;
        }
    }

    return first_header;
}


int main(int argc, char **argv)
{
    return 0;
}
