#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

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
