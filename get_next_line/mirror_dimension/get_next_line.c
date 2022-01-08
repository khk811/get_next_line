#include "get_next_line.h"
#include <stdio.h>

static char	*read_for_gnl(int fd, char **buf)
{
    int read_result;
    char result[BUFFER_SIZE];

    read_result = 0;
    read_result = read(fd, result, BUFFER_SIZE);
    if (read_result == 0 || read_result == -1)
        return (NULL);
    *buf = result;
    return (*buf);
}

char *get_next_line(int fd)
{
    //char    *result;
    char    *buf;

    buf = NULL;
    //result = NULL;
    if (BUFFER_SIZE <= 0)
    {
        printf("Buffer is too small\n");
        return (NULL);
    }
	buf = read_for_gnl(fd, &buf);
	printf("$$$%s\n", buf);
    if (!*buf)
    {
        printf("read fail\n");
        return (NULL);
    }
    return (buf);
}
