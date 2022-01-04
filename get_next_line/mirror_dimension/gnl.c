#include "gnl.h"

char    *get_next_line(int fd)
{
    char    buffer[BUFFER_SIZE];
    char    *result;
    int i;

    if (read(fd, buffer, BUFFER_SIZE) == -1)
        return (NULL);
    i = 0;
    while (buffer[i])
    {
        if (buffer[i] == '\n')
            break ;
        i++;
    }
    if (buffer[i] == '\n')
    {
        result = (char *)malloc(sizeof(char) * (i + 2));
        if (!result)
            return (NULL);
        i = 0;
        while (buffer[i] != '\n')
        {
            result[i] = buffer[i];
            i++;
        }
        result[i++] = '\n';
        result[i] = '\0';
        return (result);
    }
    else
    {
        write(1, "buffer is too small\n", 20);
        return (NULL);
    }
}
