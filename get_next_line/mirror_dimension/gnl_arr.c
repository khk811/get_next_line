#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

static int	ft_strlen(char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

static char	*cat_a_line(char *dst, char *src, int flag)
{
	int	i;
	int	j;

	i = ft_strlen(dst);
	j = 0;
	while (src[j] != '\0')
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
	if (!(*buf = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1))))
		return (0);
	if (read(fd, *buf, BUFFER_SIZE) <= 0)
		return (0);
	(*buf)[BUFFER_SIZE] = '\0';
	return (1);
}

static int	has_a_newline(char *s)
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

static void	mv_line(char **result, char **buf)
{
	char	*tmp;
	int	new_size;

	if (*result != NULL)
	{
		if (!(tmp = (char *)malloc(sizeof(char) *(ft_strlen(*result) + 1))))
			return ;
		free(*result);
		new_size = ft_strlen(tmp) + ft_strlen(*buf) + 1;
		if (!(*result = (char *)malloc(sizeof(char) * (new_size + 1))))
			return ;
		cat_a_line(*result, tmp, 0);
		cat_a_line(*result, *buf, 0);
	}
	else
	{
		if (!(*result = (char *)malloc(sizeof(char) * (ft_strlen(*buf) + 1))))
			return ;
		cat_a_line(*result, *buf, 0);
	}
}
/*
static int	check_leftover(char **leftover, char **result)
{
	int	the_nl;

	the_nl = has_a_newline(*leftover);
	if (the_nl)
	{
		*result = (char *)malloc(sizeof(char) * the_nl + 1);
		cat_a_line(*result, *leftover, 1);
		if ((*leftover)[the_nl])
		{
			return (1);
		}
	}
	else
	{
		*result = (char *)malloc(sizeof(char) * ft_strlen(*leftover) + 1);
		cat_a_line(*result, *leftover, 0);
	}
	*leftover = "";
	return (0);
}*/

char	*get_next_line(int fd)
{
	char	*buf;
	char	*result;
	int	the_nl;
	static char	*leftover = NULL;

	result = NULL;
	the_nl = 0;
	//if (leftover && check_leftover(&leftover, &result))	
	//	return (result);
	if (!valid_read(fd, &buf))
		return (NULL);
	while (!(the_nl = has_a_newline(buf)))
	{
		mv_line(&result, &buf);
		valid_read(fd, &buf);
	}
	cat_a_line(result, buf, 1);
	buf += the_nl;
	mv_line(&leftover, &buf);
	return (result);
}

int	main()
{
	int	target_fd;
	char	*the_line;
	int	i;

	target_fd = open("./test/brouette.txt", O_RDONLY);
	the_line = get_next_line(target_fd);
	i = 0;
	while (the_line && i < 10)
	{
		printf("%s", the_line);
		the_line = get_next_line(target_fd);
		i++;
	}
	/*
	printf("%s", the_line);
	the_line = get_next_line(target_fd);
	printf("%s", the_line);
	*/
	//free(the_line);
	the_line = NULL;
	return (0);
}
