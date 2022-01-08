#include "get_next_line.h"
#include <stdio.h>

static int	ft_strlen(char *s)
{
	int	i;
	
	i = 0;
	while (s[i])
		i++;
	return (i);
}

static char *ft_strncat(char *dst, char *src, int n)
{
    int i;
    int j;

    i = ft_strlen(dst);
    j = 0;
    while (src[j] && j < n)
    {
        dst[i] = src[j];
        i++;
        j++;
    }
    dst[i] = '\0';
    return (dst);
}

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

static int	cnt_wo_head(t_list **lst)
{
	t_list	*tmp;
	int	i;

    i = 0;
    tmp = *lst;
	while (tmp->next)
	{
		tmp = tmp->next;
        i++;
	}
	return (i);
}

static char	*line_return(t_list **lst, char **result, char *tail)
{
	t_list	*tmp;
	int	total_len;
	int	i;

	tmp = *lst;
	total_len = ft_strlen(tmp->content) + ft_strlen(tail);
	if (tmp->next)
		total_len += (cnt_wo_head(lst) * BUFFER_SIZE);
	*result = (char *)malloc(sizeof(char) * (total_len + 1));
	if (!*result)
		return (NULL);
	i = 0;
	while (tmp)
	{
		ft_strncat(*result, tmp->content, ft_strlen(tmp->content) + 1);
		tmp = tmp->next;
	}
	ft_strncat(*result, tail, ft_strlen(tail) + 1);
	return (*result);
}

static t_list	*create_element(char *content)
{
	t_list	*new;
	char	*new_content;

	new = malloc(sizeof(t_list));
	if (!new)
		return (NULL);
	new_content = (char *)malloc(sizeof(char) * (ft_strlen(content) + 1));
	ft_strncat(new_content, content, ft_strlen(content) + 1);
	new->content = new_content;
	new->next = NULL;
	return (new);
}

void	add_element(t_list **lst, t_list *new)
{
	t_list	*tmp;

	tmp = *lst;
	if (!*lst)
		*lst = new;
	else
	{
		while (tmp->next)
            tmp = tmp->next;
        tmp->next = new;
	}
}
static void ft_lstclear(t_list **lst)
{
    t_list  *next_element;

    while (*lst)
    {
        next_element = (*lst)->next;
        free((*lst)->content);
        *lst = next_element;
    }
}

static char	*check_newline(char *buf, t_list **lst, char *result)
{
	int	i;
	char	*tail;

	i = 0;
	tail = NULL;
	while (buf[i])
	{
		if (buf[i] == '\n')
		{
			tail = (char *)malloc(sizeof(char) * i);
			line_return(lst, &result, ft_strncat(tail, buf,  i + 1));
            ft_lstclear(lst);
			if (buf[i + 1])
				add_element(lst, create_element(buf + i + 1));
			return (result);
		}
		i++;
	}
	add_element(lst, create_element(buf));
	return (NULL);
}

char *get_next_line(int fd)
{
    char    *result;
    char    *buf;
	static t_list	*lst = NULL;

    buf = NULL;
    result = NULL;
    if (BUFFER_SIZE <= 0)
        return (NULL);
	while (!result)
	{
		if (!read_for_gnl(fd, &buf))
			return (NULL);
		result = check_newline(buf, &lst, result);
	}
    return (result);
}
