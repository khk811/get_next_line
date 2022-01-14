#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

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

static int	valid_read(int fd, char **buf)
{
	if (BUFFER_SIZE <= 0 || fd < 0)
		return (0);
	if (!(*buf = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1))))
		return (0);
	if (read(fd, *buf,BUFFER_SIZE) <= 0)
		return (0);
	(*buf)[BUFFER_SIZE] = '\0';
	return (1);
}

char	*get_next_line(int fd)
{
	char	*buf;
	//char	*result;
	//static char	*save;

	if (!valid_read(fd, &buf))
		return (NULL);
	while (!has_a_nl(buf))
		valid_read(fd, &buf);
	return (buf);
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
