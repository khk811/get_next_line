#include "get_next_line.h"
#include <stdio.h>

static void	ft_lstclear(t_list **lst, t_list *last)
{
	t_list	*tmp;
	t_list	*next_element;
	t_list	*before_tmp;

	tmp = *lst;
	before_tmp = NULL;
	while (tmp->next && tmp != last->next)
	{
		if (tmp->fd != last->fd)
			before_tmp = tmp;
		next_element = tmp->next;
		if (tmp->fd == last->fd)
		{
			tmp->content = NULL;
			free(tmp->content);
			free(tmp);
			if (before_tmp)
				before_tmp->next = next_element;
		}
		tmp = next_element;
	}
	*lst = next_element;
}

static char	*line_return(t_list **lst, char **result, t_list *last)
{
	t_list	*tmp;
	int	total_len;

	tmp = *lst;
	total_len = 0;
	while (tmp->next && tmp != last->next)
	{
		if (tmp->fd == last->fd)
			total_len += ft_strlen(tmp->content);
		tmp = tmp->next;
	}
	if(!(*result = (char *)malloc(sizeof(char) * (total_len  + 1))))
		return (NULL);
	tmp = *lst;
	while (tmp->next && tmp != last->next)
	{
		if (tmp->fd == last->fd)
			ft_strncat(*result, tmp->content, ft_strlen(tmp->content));
		tmp = tmp->next;
	}
	ft_lstclear(lst, last);
	return (*result);
}

static int	div_n_add(int fd, int is_nl, char **buf, t_list **lst)
{
	char	*buf_w_nl;
	int	is_w_nl;
	int	i;
	int	j;

	i = 0;
	j = 0;
	is_w_nl = 0;
	while (*(*(buf) + i))
	{
		if (*(*(buf) + i) == '\n')
		{
			if (!(buf_w_nl = (char *)malloc(sizeof(char) * (i - j + 2))))
				return (0);
			ft_strncat(buf_w_nl, *(buf) + j + is_w_nl, i - j + 1 - is_w_nl);
			add_element(lst, create_element(fd, 1, buf_w_nl));
			buf_w_nl = NULL;
			free(buf_w_nl);
			j = i;
			is_w_nl = 1;
		}
		i++;
	}
	add_element(lst, create_element(fd, is_nl, *(buf) + j + is_w_nl));
	return(is_w_nl);
}

static char	*read_for_gnl(int fd, char **buf, t_list **lst, char **result)
{
	int	is_nl;
	t_list	*last;

	is_nl = 0;
	if (*buf == 0)
	{
		last = last_ele(lst);
		if((*lst)->is_nl == 1 || last->is_nl == 1)
			line_return(lst, result, last_ele(lst));
	}
	else if (div_n_add(fd, is_nl, buf, lst))
		line_return(lst, result, last_ele(lst));
	return (*result);
}

char	*get_next_line(int fd)
{
	char	*result;
	char	*buf;
	static t_list	*lst = NULL;

	result = NULL;
	buf = NULL;
	if (lst)
	{
		read_for_gnl(fd, &buf, &lst, &result);
		if (result)
			return (result);
	}
	if (BUFFER_SIZE <= 0 || fd < 0)
		return (result);
	if(!(buf = (char *)malloc(sizeof(char) * BUFFER_SIZE)))
		return (NULL);
	while (!result)
	{
		if(read(fd, buf, BUFFER_SIZE) <= 0)
			return (NULL);
		read_for_gnl(fd, &buf, &lst, &result);
	}
	buf = NULL;
	free(buf);
	return (result);
}
