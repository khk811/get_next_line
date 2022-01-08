#include <stdio.h>
#include "get_next_line.h"
#include <fcntl.h>


int	main()
{
	int	target_fd;
	int	i;

	i = 0;
	target_fd = open("./read_fd_target", O_RDONLY);
	while (i++ < 19)
		printf("gnl result: %s", get_next_line(target_fd));
	return (0);
}
