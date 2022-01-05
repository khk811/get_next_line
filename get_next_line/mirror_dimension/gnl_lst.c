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
    while ((*lst)->next)
        (*lst) = (*lst)->next;
    (*lst)->next = new;
}

static int  ft_count_char(t_list **lst)
{
    int i;
    char    *content;

    i = 0;
    while (*lst)
    {
        content = (*lst)->content;
        while (*content)
        {
            if (*content == '\n')
                break;
            i++;
            content++;
        }
		if (!(*lst)->next)
			break ;
        (*lst) = (*lst)->next;
    }
    return (i);
}

static char *ft_ret_line(t_list **lst, char *arr, int len)
{
    int i;
    char    *content;
    
    i = 0;
    while (i < len)
    {
        content = (*lst)->content;
        while (*content)
        {
            arr[i++] = *content;
            content++;
        }
        (*lst) = (*lst)->next;
    }
    arr[i] = '\0';
    return (arr);
}

char    *get_next_line(int fd)
{
    char    buf[BUFFER_SIZE];
    char    *result;
	static t_list	*lst = NULL;
    int read_int;
	int	i;

    read_int = read(fd, buf, BUFFER_SIZE);
    if (read_int == -1 || read_int == 0)
        return (NULL);
    ft_gnl_lst(&lst, buf);
	i = ft_count_char(&lst);
    result = (char *)malloc(sizeof(char) * (i + 1));
    if (!result)
        return (NULL);
    ft_ret_line(&lst, result, i);
    return (result);
}
