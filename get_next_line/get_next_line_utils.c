/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunkkim <hyunkkim@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 14:32:17 by hyunkkim          #+#    #+#             */
/*   Updated: 2022/01/20 14:57:39 by hyunkkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_strlen(char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

void	*ft_memset(void *b, int c, int len)
{
	int	i;

	i = 0;
	while (i < len)
		*(unsigned char *)(b + (i++)) = (unsigned char)c;
	return ((void *)b);
}

void	*ft_memmove(void *dst, void *src, int len)
{
	int	i;

	i = 0;
	if (dst < src)
	{
		while (i < len)
		{
			*(unsigned char *)(dst + i) = *(unsigned char *)(src + i);
			i++;
		}
	}
	else if (dst > src)
	{
		while (len-- > 0)
			*(unsigned char *)(dst + len) = *(unsigned char *)(src + len);
	}
	return ((void *)dst);
}

char	*alloc_arr(char **arr, int size)
{
	char	*tmp;
	 int	tmp_len;

	tmp = NULL;
	tmp_len = 0;
	if (*arr)
	{
		tmp = (char *)malloc(sizeof(char) * (ft_strlen(*arr) + 1));
		if (!tmp)
			return (NULL);
		ft_memmove(tmp, *arr, ft_strlen(*arr) + 1);
		free(*arr);
		tmp_len = ft_strlen(tmp);
	}
	*arr = (char *)malloc(sizeof(char) * (tmp_len + size + 1));
	if (!*arr)
		return (NULL);
	ft_memset(*arr, 0, tmp_len + size + 1);
	if (tmp != NULL)
	{
		ft_memmove(*arr, tmp, tmp_len + 1);
		free(tmp);
		tmp = NULL;
	}
	return (*arr);
}

int	valid_read(int fd, char **buf)
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
		free(*buf);
		*buf = NULL;
		return (0);
	}
	(*buf)[read_result] = '\0';
	return (1);
}
