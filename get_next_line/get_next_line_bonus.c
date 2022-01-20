/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunkkim <hyunkkim@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 14:32:12 by hyunkkim          #+#    #+#             */
/*   Updated: 2022/01/20 14:57:35 by hyunkkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

static t_list	*find_fd(t_list **lst, int fd)
{
	t_list	*tmp;

	tmp = *lst;
	if (!*lst || !lst)
		return (NULL);
	if (tmp->fd == fd)
		return (tmp);
	while (tmp->next && tmp->fd != fd)
		tmp = tmp->next;
	if (tmp->fd != fd)
		return (NULL);
	return (tmp);
}

static void	rm_element(t_list **lst, int fd)
{
	t_list	*tmp;
	t_list	*before;

	before = NULL;
	tmp = *lst;
	if (!*lst || !lst)
		return ;
	if (!tmp->next)
	{
		free(*lst);
		*lst = NULL;
		lst = NULL;
		return ;
	}
	while (tmp->next && tmp->fd != fd)
	{
		before = tmp;
		tmp = tmp->next;
	}
	if (before)
		before->next = tmp->next;
	if (!before)
		*lst = tmp->next;
	free(tmp);
	tmp = NULL;
}

static void	add_new_element(t_list **lst, int fd, char *buf)
{
	t_list	*tmp;
	t_list	*new;

	tmp = find_fd(lst, fd);
	if (tmp)
	{
		tmp->buf = buf;
		return ;
	}
	tmp = *lst;
	new = malloc(sizeof(t_list));
	if (!new)
		return ;
	new->fd = fd;
	new->buf = buf;
	new->next = NULL;
	if (!*lst)
		*lst = new;
	else
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}

char	*get_next_line(int fd)
{
	static t_list	*fd_lst = NULL;
	       t_list	*matching_fd;
	         char	*buf;
	         char	*result;

	result = NULL;
	buf = NULL;
	matching_fd = find_fd(&fd_lst, fd);
	if (matching_fd)
		buf = matching_fd->buf;
	if (!buf)
		valid_read(fd, &buf);
	while (buf)
	{
		if (!alloc_arr(&result, ft_strlen(buf)))
			break ;
		if (read_until(&buf, &result))
			break ;
		valid_read(fd, &buf);
	}
	if (find_fd(&fd_lst, fd) && !buf)
		rm_element(&fd_lst, fd);
	else if (buf)
		add_new_element(&fd_lst, fd, buf);
	return (result);
}
