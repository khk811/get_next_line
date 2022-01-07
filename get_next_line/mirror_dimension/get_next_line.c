#include "get_next_line.h"
#include <stdio.h>

static int read_for_gnl(int fd, char **buf)
{
    int read_result;
    char result[BUFFER_SIZE];

    read_result = 0;
    read_result = read(fd, result, BUFFER_SIZE);
    if (read_result == 0 || read_result == -1)
        return (0);
    *buf = result;
    //printf(">>%s\n", *buf);
    return (1);
}

char *get_next_line(int fd)
{
    //char    *result;
    char    *buf;

    buf = NULL;
    //result = NULL;
    if (BUFFER_SIZE < 0)
    {
        printf("Buffer is too small\n");
        return (NULL);
    }
    if (!read_for_gnl(fd, &buf))
    {
        printf("read fail\n");
        return (NULL);
    }
    if (!buf)
        printf("can't write to buf\n");
    return (buf);
}
