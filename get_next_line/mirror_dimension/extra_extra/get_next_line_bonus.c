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
			{
				printf("&&& the leftover: %s &&&\n", (*buf) + i);
				ft_memmove((*buf), (*buf) + i, ft_strlen((*buf) + i) + 1);
			}
			else if (*buf)
			{
				puts("&&& rm buf &&&\n");
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
		puts("((init lst))\n");
		return ((*lst));
	}
	while (tmp)
	{
		if (tmp->fd == fd)
		{
			puts("((found fd))\n");
			break ;
		}
		printf("((curr *lst fd: %d))\n", (tmp)->fd);
		if (tmp->next != NULL)
			tmp = tmp->next;
	}
	printf("((no fd founded, curr *lst fd: %d))\n", (tmp)->fd);
	if (tmp->fd != fd)
	{
		tmp->next = create_element(fd);
		tmp = tmp->next;
		puts("((new fd))\n");
	}
	return (tmp);
}

static void	 rm_element(t_list **lst, int fd)
{
	t_list	*tmp;
	t_list	*before;

	before = NULL;
	tmp = *lst;
	puts("!!!! the inside of rm_element !!!!\n");
	if (!tmp)
		return ;
	while (tmp->next)
	{
		if (tmp->fd != fd)
			before = tmp;
		if (tmp->fd == fd)
			break ;
		printf("!!!! curr *lst->fd: %d !!!!\n", (tmp)->fd);
		if (tmp->next != NULL)
			tmp = tmp->next;
	}
	if (before)
	{
		printf("!!!! the before fd: %d !!!!\n", before->fd);
		before->next = tmp->next;
	}
	printf("!!!! rm target fd: %d !!!!\n", (tmp)->fd);
	free(tmp);
	tmp = NULL;
}

static int	valid_read(int fd, char **buf)
{
	int	read_result;

	if (!*buf)
	{
		if (!alloc_arr(buf, BUFFER_SIZE))
			return (0);
	}
	else if (*buf)
	{
		printf("### before memset: %s ###\n", *buf);
		ft_memset(*buf, 0, ft_strlen(*buf) + 1);
	}
	read_result = read(fd, *buf, BUFFER_SIZE);
	if (read_result <= 0)
	{
		if (*buf)
		{
			printf("### read fail buf: %s ###\n", *buf);
			free(*buf);
		}
		*buf = NULL;
		printf("### the rm fd: %d ###\n", fd);
		return (0);
	}
	(*buf)[read_result] = '\0';
	return (1);
}

char	*get_next_line(int fd)
{
	static t_list	*fd_lst = NULL;
	t_list	*matching_fd;
	char	*fd_buf;
	char	*result;
	int	is_valid;

	result = NULL;
	is_valid = 0;
	if (BUFFER_SIZE <= 0 || fd < 0)
		return (result);
	matching_fd = find_fd(fd, &fd_lst);
	fd_buf = matching_fd->buf;
	if (fd_buf)
		printf("++++ curr leftover: %s ++++\n", fd_buf);
	if (!fd_buf)
	{
		is_valid = valid_read(fd, &(fd_buf));
		if (!is_valid)
			rm_element(&fd_lst, fd);
	}
	while (is_valid || fd_buf)
	{
		if (!alloc_arr(&result, ft_strlen(fd_buf)))
			break ;
		if (read_until(&(fd_buf), &result))
			return (result);
		is_valid = valid_read(fd, &(fd_buf));
	}
	return (result);
}
