#include "get_next_line.h"
#include <stdio.h>

static int	ft_strlen(char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

static void	*ft_memset(void *b, int c, int len)
{
	int	i;

	i = 0;
	while (i < len)
		*(unsigned char *)(b + (i++)) = (unsigned char)c;
	return ((void *)b);
}

static void	*ft_memmove(void *dst, void *src, int len)
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

static char	*alloc_arr(char **arr, int size)
{
	char	*tmp;

	tmp = NULL;
	if (!*arr)
	{
		if(!(*arr = (char *)malloc(sizeof(char) * (size + 1))))
			return (NULL);
		ft_memset(*arr, 0, size + 1);
	}
	else if (*arr)
	{
		if (!(tmp = (char *)malloc(sizeof(char) * (ft_strlen(*arr) + 1))))
			return (NULL);
		ft_memset(tmp, 0, ft_strlen(*arr) + 1);
		ft_memmove(tmp, *arr, ft_strlen(*arr) + 1);
		free(*arr);
		*arr = (char *)malloc(sizeof(char) * (ft_strlen(tmp) + size + 1));
		if (!*arr)
			return (NULL);
		ft_memset(*arr, 0, ft_strlen(tmp) + size + 1);
		ft_memmove(*arr, tmp, ft_strlen(tmp) + 1);
		free(tmp);
	}
	return (*arr);
}

static int	valid_read(int fd, char **buf)
{
	int	read_result;

	read_result = 0;
	if (BUFFER_SIZE <= 0 || fd < 0)
		return (0);
	if (!alloc_arr(buf, BUFFER_SIZE))
		return (0);
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
				ft_memmove((*buf), (*buf) + i, ft_strlen((*buf) + i) + 1); 
				//alloc_arr(buf, ft_strlen(*buf));
			}
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
	return (result);
}
