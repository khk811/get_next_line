#include "gnl.h"
#include <fcntl.h>

int main()
{
    int target_fd;
    char    *result;

    target_fd = open("./read_fd_target", O_RDONLY);
    result = get_next_line(target_fd);
    if (result)
    {
        while (*result)
            write(1, result++, 1);
    }
    return (0);
}
