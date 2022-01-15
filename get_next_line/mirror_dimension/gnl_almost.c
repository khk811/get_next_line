#include "get_next_line.h"

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

static int	has_a_nl(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '\n')
			return (i + 1);
		i++;
	}
	return (0);
}

static char	*cat_a_line(char *dst, char *src, int flag)
{
	int	i;
	int	j;

	i = ft_strlen(dst);
	j = 0;
	while (src[j])
	{
		if (src[j] == '\n' && flag == 1)
		{
			dst[i++] = src[j];
			break ;
		}
		dst[i] = src[j];
		i++;
		j++;
	}
	dst[i] = '\0';
	return (dst);
}

static char	*alloc_arr(char **arr, int size)
{
	char	*tmp;

	tmp = NULL;
	if (!*arr)
	{
		if(!(*arr = (char *)malloc(sizeof(char) * (size + 1))))
			return (NULL);
	}
	else if (*arr && size > 0)
	{
		if (!(tmp = (char *)malloc(sizeof(char) * (ft_strlen(*arr) + 1))))
			return (NULL);
		cat_a_line(tmp, *arr, 0);
		ft_memset(*arr, 0, ft_strlen(*arr));
		free(*arr);
		*arr = (char *)malloc(sizeof(char) * (ft_strlen(tmp) + size + 1));
		if (!*arr)
			return (NULL);
		cat_a_line(*arr, tmp, 0);
		ft_memset(tmp, 0, ft_strlen(tmp) + 1);
		free(tmp);
	}
	return (*arr);
}

static int	valid_read(int fd, char **buf, char **save)
{
	if (*save)
	{
		if (alloc_arr(buf, ft_strlen(*save)))
			cat_a_line(*buf, *save, 0);
		ft_memset(*save, 0, ft_strlen(*save) + 1);
		free(*save);
		*save = NULL;
		return (1);
	}
	if (BUFFER_SIZE <= 0 || fd < 0)
		return (0);
	if (!alloc_arr(buf, BUFFER_SIZE))
		return (0);
	if(read(fd, *buf, BUFFER_SIZE) <= 0)
	{
		if (*buf)
			free(*buf);
		*buf = NULL;
		return (0);
	}
	(*buf)[BUFFER_SIZE] = '\0';
	return (1);
}

static int	read_for_gnl(int fd, char **buf, char **result, char **save)
{
	int	the_nl;
	int	is_valid;

	is_valid = valid_read(fd, buf, save);
	if (!is_valid)
		return (0);
	the_nl = has_a_nl(*buf);
	while (!the_nl && is_valid)
	{
		if (alloc_arr(result, ft_strlen(*buf)))
			cat_a_line(*result, *buf, 0);
		ft_memset(*buf, 0, ft_strlen(*buf) + 1);
		free(*buf);
		*buf = NULL;
		is_valid = valid_read(fd, buf, save);
		if (is_valid)
			the_nl = has_a_nl(*buf);
		else
		{
			if (*save)
				free(*save);
			return (1);
		}
	}
	if (alloc_arr(result, the_nl))
		cat_a_line(*result, *buf, 1);
	if ((*buf)[the_nl])
	{
		if (alloc_arr(save, ft_strlen(*(buf) + the_nl)))
			cat_a_line(*save,*(buf) + the_nl, 0);
	}
	return (1);
}

char	*get_next_line(int fd)
{
	char	*buf;
	char	*result;
	static char	*save = NULL;

	result = NULL;
	buf = NULL;
	if(!read_for_gnl(fd, &buf, &result, &save))
		return (NULL);
	if (buf)
	{
		ft_memset(buf, 0, ft_strlen(buf) + 1);
		free(buf);
	}
	buf = NULL;
	return (result);
}
