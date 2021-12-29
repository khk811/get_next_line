#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

char    *get_next_line(int fd)
{
    static char buffer[1];
    static char result[100];
    int i;

    i = 0;
    while (read(fd, buffer, 1))
    {
        result[i] = buffer[0];
        if (result[i] == '\n')
            return (result);
        i++;
    }
    return (0);
}

int main()
{
    int target_fd;
    char    *result;

    target_fd = open("./read_fd_target", O_RDONLY);
    result = get_next_line(target_fd);
    while (result)
    {
        printf("%s", result);
        result = get_next_line(target_fd);
    }
    return (0);
}
