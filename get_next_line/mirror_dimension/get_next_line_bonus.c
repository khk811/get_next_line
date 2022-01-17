#include "get_next_line_bonus.h"
#include <stdio.h>

static char	*read_until(char **buf, char **result)
{
	int	i;
	int	j;

	j = ft_strlen(*result);
	i = 0;
	while ((*buf)[i])
	{
		if ((*buf)[i] == '\n')
		{
			(*result)[j] = (*buf)[i++];
			alloc_arr(result, 0);
			if ((*buf)[i])
				ft_memmove((*buf), (*buf) + i, ft_strlen((*buf) + i) + 1);
			else if (*buf)
			{
				free(*buf);
				*buf = NULL;
			}
			return (*result);
		}
		(*result)[j++] = (*buf)[i++];
	}
	return (NULL);
}

static t_list	*find_fd(int fd, t_list **lst)
{
	if (!*lst)
	{
		*lst = create_element(fd);
		return (*lst);
	}
	while ((*lst)->next)
	{
		if ((*lst)->fd == fd)
			break ;
		*lst = (*lst)->next;
	}
	if ((*lst)->fd != fd)
	{
		(*lst)->next = create_element(fd);
		*lst = (*lst)->next;
	}
	return (*lst);
}

static void	 rm_element(t_list **lst, int fd)
{
	t_list	*before;

	before = NULL;
	if (!*lst)
		return ;
	while (*lst)
	{
		if ((*lst)->fd != fd)
			before = *lst;
		if ((*lst)->fd == fd)
			break ;
		*lst = (*lst)->next;
	}
	if (before)
		before->next = (*lst)->next;
	free(*lst);
	*lst = NULL;
}

static int	valid_read(int fd, char **buf, t_list **lst)
{
	int	read_result;

	if (BUFFER_SIZE <= 0 || fd < 0)
		return (0);
	if (!*buf)
	{
		if (!alloc_arr(buf, BUFFER_SIZE))
			return (0);
	}
	else if (*buf)
		ft_memset(*buf, 0, ft_strlen(*buf) + 1);
	read_result = read(fd, *buf, BUFFER_SIZE);
	if (read_result <= 0)
	{
		if (*buf)
			free(*buf);
		*buf = NULL;
		rm_element(lst, fd);
		return (0);
	}
	(*buf)[read_result] = '\0';
	return (1);
}

char	*get_next_line(int fd)
{
	static t_list	*buf = NULL;
	char	*result;
	t_list	*the_fd;

	result = NULL;
	the_fd = find_fd(fd, &buf);
	if (the_fd)
	{
		if (!(the_fd->buf)) 
			valid_read(fd, &(the_fd->buf), &buf);
	}
	while (the_fd && (the_fd->buf))
	{
		if (!alloc_arr(&result, ft_strlen(the_fd->buf)))
			break ;
		if (read_until(&(the_fd->buf), &result))
			return (result);
		valid_read(fd, &(the_fd->buf), &buf);
	}
	return (result);
}
