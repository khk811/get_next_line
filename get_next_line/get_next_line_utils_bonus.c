#include "get_next_line_bonus.h"
#include <stdio.h>

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

	tmp = NULL;
	if (!*arr)
	{
		*arr = (char *)malloc(sizeof(char) * (size + 1));
		if (!*arr)
			return (NULL);
		ft_memset(*arr, 0, size + 1);
	}
	else if (*arr)
	{
		tmp = (char *)malloc(sizeof(char) * (ft_strlen(*arr) + 1));
		if (!tmp)
			return (NULL);
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
	if (read_result <= 0 && *buf)
	{
		free(*buf);
		*buf = NULL;
		return (0);
	}
	(*buf)[read_result] = '\0';
	return (1);
}
