#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

int	main()
{
	char	*a_line;
	int	target_fd;

	target_fd = open("./test/brouette.txt", O_RDONLY);
	printf("[[target_fd: %d]]\n---------\n", target_fd);
	a_line = get_next_line(target_fd);
	printf("%s\n", a_line);
	a_line = get_next_line(target_fd);
	printf("%s\n", a_line);
	a_line = get_next_line(target_fd);
	printf("%s\n", a_line);
	/*
	while (a_line)
	{
		printf("%s", a_line);
		a_line = get_next_line(target_fd);
	}*/
	free(a_line);
	return (0);
}
