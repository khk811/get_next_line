#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

typedef struct s_list
{
    void    *content;
    struct s_list   *next;
}   t_list;

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
    t_list  **result;
    t_list  *element;
    t_list  *new;

    target_fd = open("./read_fd_target", O_RDONLY);
    element = malloc(sizeof(t_list));
    element->content = "";
    element->next = NULL;
    result = &element;
    while (element)
    {
        new = malloc(sizeof(t_list));
        new->content = get_next_line(target_fd);
        if (!(new->content))
            break ;
        while (*(char *)(new->content))
            write(1, (new->content)++, 1);
        new->next = NULL;
        element->next = new;
        element = element->next;
    }
    return (0);
}
