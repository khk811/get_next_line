#include "gnl.h"
#include <stdio.h>

typedef struct  s_list
{
    void    *content;
    struct s_list   *next;
}   t_list;

static void ft_gnl_lst(t_list **lst, void *content)
{
    t_list  *new;
    t_list  *element;

    new = malloc(sizeof(t_list));
    if (!new)
        return ;
    new->content = content;
    new->next = NULL;
    if (!*lst)
    {
        *lst = new;
        return ;
    }
    element = *lst;
    while (element->next)
        element = element->next;
    element->next = new;
}

static int  ft_count_char(t_list **lst)
{
    int i;
    t_list  *element;
    char    *content;

    i = 0;
    element = *lst;
    while (element)
    {
        content = element->content;
        while (*content)
        {
            if (*content == '\n')
                break;
            i++;
            content++;
        }
        element = element->next;
    }
    return (i);
}

static char *ft_ret_line(t_list **lst, char *arr, int len)
{
    int i;
    t_list  *element;
    char    *content;
    
    i = 0;
    element = *lst;
    while (i < len)
    {
        content = element->content;
        while (*content)
        {
            arr[i++] = *content;
            content++;
        }
        element = element->next;
    }
    arr[i] = '\0';
    return (arr);
}

char    *get_next_line(int fd)
{
    char    buf[BUFFER_SIZE];
    char    *result;
    static t_list  **lst;
    t_list  *dummy;
    int read_int;
    int i;

    read_int = read(fd, buf, BUFFER_SIZE);
    if (read_int == -1)
        return (NULL);
    else if (read_int < BUFFER_SIZE)
        return (NULL) ;
    dummy = malloc(sizeof(t_list));
    dummy->content = "";
    dummy->next = NULL;
    lst = &dummy;
    if (!lst)
        printf("**lst is null\n");
    ft_gnl_lst(lst, buf);
    i = ft_count_char(lst);
    result = (char *)malloc(sizeof(char) * (i + 1));
    if (!result)
        return (NULL);
    ft_ret_line(lst, result, i);
    return (result);
}
