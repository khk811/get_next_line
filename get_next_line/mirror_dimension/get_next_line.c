#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

static int	ft_strlen(char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

static char	*alloc_arr(char **arr, int size)
{
	if (!*arr)
	{
		*arr = (char *)malloc(sizeof(char) * (size + 1));
		if (!*arr)
			return (NULL);
	}
	/*
	else if (*arr)
	{
	}*/
	return (*arr);
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

static int	valid_read(int fd, char **buf)
{
	if (BUFFER_SIZE <= 0 || fd < 0)
		return (0);
	if (!alloc_arr(buf, BUFFER_SIZE))
		return (0);
	if (read(fd, *buf, BUFFER_SIZE) <= 0)
		return (0);
	(*buf)[BUFFER_SIZE] = '\0';
	return (1);
}

char	*get_next_line(int fd)
{
	char	*buf;
	char	*result;
	//static char	*save;

	result = NULL;
	buf = NULL;
	if (!valid_read(fd, &buf))
		return (NULL);
	alloc_arr(&result, ft_strlen(buf));
	result[ft_strlen(buf)] = '\0';
	cat_a_line(result, buf, 0);
	has_a_nl(buf);
	/*
	while (!has_a_nl(buf))
	{
		alloc_arr(result, ft_strlen(buf));
		cat_a_line(result, buf, 0);
		valid_read(fd, &buf);
	}*/
	return (result);
}

int	main()
{
	int	target_fd;
	char	*a_line;

	target_fd = open("./test/brouette.txt", O_RDONLY);
	a_line = get_next_line(target_fd);
	printf("%s\n", a_line);
	free(a_line);
	return (0);
}
