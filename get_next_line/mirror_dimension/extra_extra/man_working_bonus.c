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
	t_list	*tmp;

	tmp = *lst;
	if (!*lst)
	{
		*lst = create_element(fd);
		return (*lst);
	}
	while (tmp && tmp->next)
	{
		if (tmp->fd == fd)
			break ;
		tmp = tmp->next;
	}
	if (tmp->fd != fd)
	{
		tmp->next = create_element(fd);
		tmp = tmp->next;
	}
	return (tmp);
}

static void	 rm_element(t_list **lst, int fd)
{
	t_list	*tmp;
	t_list	*before;

	tmp = *lst;
	before = NULL;
	if (!*lst)
		return ;
	while (tmp)
	{
		if (tmp->fd != fd)
			before = tmp;
		if (tmp->fd == fd)
			break ;
		tmp = tmp->next;
	}
	if (before)
		before->next = tmp->next;
	free(tmp);
	tmp = NULL;
}

static int	valid_read(int fd, char **buf)
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
		return (0);
	}
	(*buf)[read_result] = '\0';
	return (1);
}

char	*get_next_line(int fd)
{
	static t_list	*buf = NULL;
	t_list	*matching_fd;
	char	*result;
	int	is_valid;

	result = NULL;
	is_valid = 0;
	matching_fd = find_fd(fd, &buf);
	if (!(matching_fd->buf))
	{
		is_valid = valid_read(fd, &(matching_fd->buf));
		if (!is_valid && matching_fd)
			rm_element(&buf, fd);
	}
	while (is_valid || (matching_fd->buf))
	{
		if (!alloc_arr(&result, ft_strlen(matching_fd->buf)))
			break ;
		if (read_until(&(matching_fd->buf), &result))
			return (result);
		is_valid = valid_read(fd, &(matching_fd->buf));
	}
	/*
	if (!is_valid)
		rm_element(&buf, fd);
		*/
	return (result);
}
