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

static void	*ft_memcpy(void *dst, void *src, int n)
{
	int	i;

	if (!dst && !src)
		return (NULL);
	i = 0;
	while (i < n)
	{
		*(unsigned char *)(dst + i) = *(unsigned char *)(src + i);
		i++;
	}
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
	tmp = (*lst)->next;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
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
		total_len += cnt_wo_head(lst);
	*result = (char *)malloc(sizeof(char) * total_len);
	if (!*result)
		return (NULL);
	i = 0;
	while (tmp)
	{
		ft_memcpy(*(result + i), tmp->content, ft_strlen(tmp->content));
		i += ft_strlen(tmp->content);
		tmp = tmp->next;
	}
	ft_memcpy(*(result + i), tail, ft_strlen(tail));
	return (*result);
}

static t_list	*create_element(char *content)
{
	t_list	*new;
	char	*new_content;

	new = malloc(sizeof(t_list));
	if (!new)
		return (NULL);
	new_content = (char *)malloc(sizeof(char) * ft_strlen(content));
	ft_memcpy(new_content, content, ft_strlen(content));
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
		while (tmp)
		{
			if (!tmp->next)
			{
				new = tmp->next;
				return ;
			}
			tmp = tmp->next;
		}
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
			line_return(lst, &result, ft_memcpy(tail, buf, i));
			if (buf[i + 1])
				add_element(lst, create_element(buf + i));
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
	static t_list	*lst;

    buf = NULL;
	lst = NULL;
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
