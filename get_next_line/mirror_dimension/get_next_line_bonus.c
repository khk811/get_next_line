#include "get_next_line_bonus.h"

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

static t_list	*handling_fd(int fd, t_list **lst)
{
	t_list	*tmp;

	tmp = *lst;
	if (!tmp)
		tmp = create_element(fd);
	else if (tmp)
	{
		while (tmp->next)
		{
			if (tmp->fd == fd)
				break ;
			tmp = tmp->next;
		}
	}
	else if (tmp->fd != fd)
	{
		tmp->next = create_element(fd);
		tmp = tmp->next;
	}
	return (tmp);
}
static void	free_element(int fd, t_list **lst)
{
	t_list	*tmp;

	tmp = *lst;
	while (tmp->next)
	{
		if (tmp->fd == fd && tmp->buf)
		{
			ft_memset(tmp->buf, 0, ft_strlen(tmp->buf) + 1);
			free(tmp->buf);
			tmp->buf = NULL;
			break ;
		}
		tmp = tmp->next;
	}
	if (tmp)
	{
		ft_memset(tmp->buf, 0, ft_strlen(tmp->buf) + 1);
		free(tmp->buf);
	}
	tmp->buf = NULL;
	free(tmp);
	tmp = NULL;
}

static t_list	*valid_read(int fd, t_list **lst)
{
	int	read_result;
	t_list	*ret;

	if (BUFFER_SIZE <= 0 || fd < 0)
		return (NULL);
	ret = handling_fd(fd, lst);
	if (!ret && !(alloc_arr(&(ret->buf), BUFFER_SIZE)))
		return (NULL);
	read_result = read(fd, ret->buf, BUFFER_SIZE);
	if (read_result <= 0)
	{
		if (ret)
			free_element(fd, lst);
		lst = NULL;
		return (NULL);
	}
	(ret->buf)[read_result] = '\0';
	return (ret);
}

char	*get_next_line(int fd)
{
	static t_list	*fd_lst = NULL;
	       t_list	*the_fd;
	         char	*result;

	result = NULL;
	the_fd = valid_read(fd, &fd_lst);
	if (the_fd && !(the_fd->buf))
		the_fd = valid_read(fd, &fd_lst);
	while (the_fd || (the_fd->buf))
	{
		if (!alloc_arr(&result, ft_strlen((the_fd->buf))))
			break ;
		if (read_until(&(the_fd->buf), &result))
			return (result);
		the_fd = valid_read(fd, &fd_lst);
	}
	if (!the_fd && result)
		free_element(fd, &fd_lst);
	return (result);
}
