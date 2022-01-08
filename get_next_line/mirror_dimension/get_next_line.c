#include "get_next_line.h"
#include <stdio.h>

static char	*read_for_gnl(int fd, char **buf)
{
    int read_result;

    read_result = 0;
	*buf = (char *)malloc(sizeof(char) * (BUFFER_SIZE));
    read_result = read(fd, *buf, BUFFER_SIZE);
    if (read_result == 0 || read_result == -1)
        return (NULL);
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
	read_for_gnl(fd, &buf);
    if (!*buf)
    {
        printf("read fail\n");
        return (NULL);
    }
    return (buf);
}
