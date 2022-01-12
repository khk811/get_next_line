#include "get_next_line.h"

static char	*line_return(char **dst, char **result)
{

}

static char	*mv_n_check(char *dst, char *src, char **result)
{
	int	i;

	i = 0;
	while (src[i])
	{
		dst[i] = src[i];
		if (dst[i] == '\n')
		{
			line_return(&dst, result);
		}
		i++;
	}
}

char	*get_next_line(int fd)
{
	char	*buf;
	char	*result;
	static char	*leftover;

	if (BUFFER_SIZE <= 0 || fd < 0)
		return(NULL);
	if (!(buf = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1))))
		return (NULL);
	if (read(fd, buf, BUFFER_SIZE) <= 0)
		return (NULL);
	buf[BUFFER_SIZE] = '\0';
}
