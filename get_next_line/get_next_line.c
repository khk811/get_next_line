/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunkkim <hyunkkim@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 14:32:07 by hyunkkim          #+#    #+#             */
/*   Updated: 2022/01/20 20:54:08 by hyunkkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

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
			if (!alloc_arr(result, 0))
				j = -1;
			if ((*buf)[i])
				ft_memmove((*buf), (*buf) + i, ft_strlen((*buf) + i) + 1);
			else if (*buf || j == -1)
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

char	*get_next_line(int fd)
{
	static char	*buf = NULL;
	       char	*result;
	        int	is_valid;

	result = NULL;
	is_valid = 0;
	if (!buf)
		is_valid = valid_read(fd, &buf);
	while (is_valid || buf)
	{
		if (!alloc_arr(&result, ft_strlen(buf)))
			break ;
		if (read_until(&buf, &result))
			return (result);
		is_valid = valid_read(fd, &buf);
	}
	if (buf && !result)
		free(buf);
	buf = NULL;
	return (result);
}
