#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>

typedef struct  s_list
{
    void    *content;
    struct s_list   *next;
}   t_list;

char *get_next_line(int fd);

#endif
