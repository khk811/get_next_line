#include "get_next_line.h"
#include <stdio.h>

static char	*read_for_gnl(int fd, char **buf)
{
	int	read_result;

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
	total_len = ft_strlen(tail);
	if (tmp)
	{
		total_len += ft_strlen(tmp->content);
		if (tmp->next)
			total_len += (cnt_wo_head(lst) * BUFFER_SIZE);
	}
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
			line_return(lst, &result, ft_strncat(tail, buf, i + 1));
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

char	*get_next_line(int fd)
{
	char	*result;
	char	*buf;
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
	free(buf);
	return (result);
}
