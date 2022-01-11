#include "ex_gnl_lst.h"
#include <stdio.h>

static int	ft_strlen(char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

static char	*ft_strncat(char *dst, char *src, int size)
{
	int	i;
	int	j;

	i = ft_strlen(dst);
	j = 0;
	while (src[j] && j < size)
	{
		dst[i] = src[j];
		i++;
		j++;
	}
	dst[i] = '\0';
	return (dst);
}

static t_list	*create_element(int fd, int nl_eof, char *content)
{
	t_list	*new;

	new = malloc(sizeof(t_list));
	if (!new)
		return (NULL);
	new->content = (char *)malloc(sizeof(char) * ft_strlen(content) + 1);
	ft_strncat(new->content, content, ft_strlen(content));
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
	{
		*lst = new;
		return ;
	}
	else
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}

static void	ft_lstclear(t_list **lst, t_list *last)
{
	t_list	*tmp;
	t_list	*next_element;
	t_list	*diff_fd;

	tmp = *lst;
	diff_fd = NULL;
	while (tmp->next && tmp != last)
	{
		if (tmp->fd != last->fd)
			diff_fd = tmp;
		next_element = tmp->next;
		if (tmp->fd == last->fd)
		{
			free(tmp->content);
		}
		tmp = next_element;
	}
	printf("before free: %s\n", tmp->content);
	free(tmp->content);
}

static char	*line_return(t_list **lst, char **result, t_list *last)
{
	t_list	*tmp;
	int	total_len;

	tmp = *lst;
	total_len = 0;
	while (tmp->next && tmp->nl_eof != 1)
	{
		if (tmp->fd == last->fd && tmp->nl_eof != 1)
			total_len += ft_strlen(tmp->content);
		tmp = tmp->next;
	}
	total_len += ft_strlen(last->content);
	*result = (char *)malloc(sizeof(char) * (total_len  + 1));
	if (!result)
		return (NULL);
	tmp = *lst;
	while (tmp->next && tmp->nl_eof != 1)
	{
		if (tmp->fd == last->fd && tmp->nl_eof != 1)
			ft_strncat(*result, tmp->content, ft_strlen(tmp->content));
		tmp = tmp->next;
	}
	ft_strncat(*result, tmp->content, ft_strlen(tmp->content));
	ft_lstclear(lst, last);
	return (*result);
}

static int	check_nl_eof(int fd, int nl_eof, char **buf, t_list **lst)
{
	char	*buf_w_nl;
	int	is_nl_eof;
	int	i;
	int	j;

	i = 0;
	j = 0;
	is_nl_eof = 0;
	while (*(*(buf) + i))
	{
		if (*(*(buf) + i) == '\n')
		{
			if (!(buf_w_nl = (char *)malloc(sizeof(char) * (i - j + 2))))
				return (0);
			ft_strncat(buf_w_nl, *(buf) + j + is_nl_eof, i - j + 1 - is_nl_eof);
			add_element(lst, create_element(fd, 1, buf_w_nl));
			buf_w_nl = NULL;
			free(buf_w_nl);
			j = i;
			is_nl_eof = 1;
		}
		i++;
	}
	add_element(lst, create_element(fd, nl_eof, *(buf) + j + is_nl_eof));
	return(is_nl_eof);
}

static void	find_last(t_list **last)
{
	if (!last)
		return ;
	else if (!*last)
		return ;
	//printf("*last->content: %s\n", (*last)->content);
	while ((*last)->next && (*last)->nl_eof != 1)
		(*last) = (*last)->next;
}

static char	*read_for_gnl(int fd, char **buf, t_list **lst, char **result)
{
	int	read_result;
	int	nl_eof;
	t_list	*last;

	nl_eof = 0;
	*buf = (char *)malloc(sizeof(char) * BUFFER_SIZE);
	read_result = read(fd, *buf, BUFFER_SIZE);
	if (read_result == 0 || read_result == -1)
		return (NULL);
	if (read_result < BUFFER_SIZE)
		nl_eof = 1;
	if (check_nl_eof(fd, nl_eof, buf, lst))
	{
		last = *lst;
		find_last(&last);
		line_return(lst, result, last);
	}
	return (*result);
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
		read_for_gnl(fd, &buf, &lst, &result);
	free(buf);
	buf = NULL;
	if (lst)
		printf("lst content: %s\n", lst->content);
	return (result);
}
