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

static char	*ft_strcat(char *dst, char *src)
{
	int	i;
	int	j;

	i = ft_strlen(dst);
	j = 0;
	while (src[j])
	{
		dst[i] = src[j];
		i++;
		j++;
	}
	dst[i] = '\0';
	return (dst);
}

static t_list	create_element(int fd, int nl_eof, char *content);
{
	t_list	*new;
	char	*new_content;

	new = malloc(sizeof(t_list));
	if (!new)
		return (NULL);
	new->content = (char *)malloc(sizeof(char) * ft_strlen(content) + 1);
	ft_strcat(new_content, content);
	new->fd = fd;
	new->nl_eof = nl_eof;
	new->next = NULL;
	return (new);
}

static void	add_element(t_list **lst, t_list *new)
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

static char	*line_return(t_list **lst, char **result, t_list *last)
{
	t_list	*tmp;
	int	total_len;

	tmp = *lst;
	total_len = 0;
	while (tmp->next)
	{
		if (tmp->fd == last->fd)
			break ;
		tmp = tmp->next;
	}
	tmp = *lst;
	while (tmp->next && tmp->fd == last->fd)
	{
		total_len += ft_strlen(tmp->content);
		tmp = tmp->next;
	}
	total_len += ft_strlen(last->content);
	*result = (char *)malloc(sizeof(char) * (total_len  + 1));
	if (!result)
		return (NULL);
	tmp = *lst;
	while (tmp->next && tmp->fd == last->fd)
	{
		ft_strcat(&result, tmp->content);
		tmp = tmp->next;
	}
	return (result);
}

static void	check_nl_eof()
{
	char	*buf_w_nl;

}

static void	read_for_gnl(int fd, char **buf, t_list **lst)
{
	int	read_result;
	int	nl_eof;
	char	*buf_w_nl;
	int	i;

	nl_eof = 0;
	*buf = (char *)malloc(sizeof(char) * BUFFER_SIZE);
	read_result = read(fd, *buf, BUFFER_SIZE);
	if (read_result == 0 || read_result == -1)
	{
		free(*buf);
		return (NULL);
	}
	if (read(fd, *buf, BUFFER_SIZE) < BUFFER_SIZE)
		nl_eof = 1;
	while (buf[i])
	{
		if (buf[i])
		{
			nl_eof = 1;
			ft_strcat(buf_w_nl, buf);
			add_element(lst, create_element(fd, nl_eof, buf));
			//add newline element.
			break ;
		}
		i++;
	}
	//add leftover element
	//need to separate - func.
}

char	*get_next_line(int fd)
{
	char	*result;
	char	*buf;
	static t_list	*lst = NULL;

	result = NULL;
	buf = NULL;
	if (BUFFER_SIZE <= 0)
		return (result);
	while (!result)
	{
	}
}
