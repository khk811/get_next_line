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
		return (tmp);
	}
	while (tmp && tmp->next)
	{
		if (tmp->fd == fd)
		{
			puts("((found fd))\n");
			break ;
		}
		printf("((curr *lst fd: %d))\n", (tmp)->fd);
		tmp = (tmp)->next;
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
		printf("++++ curr head fd: %d ++++\n", the_fd->fd);
		if (the_fd->buf)
			printf("++++ curr leftover: %s ++++\n", the_fd->buf);
	}
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
