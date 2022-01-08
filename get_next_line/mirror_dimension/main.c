#include <stdio.h>
#include "get_next_line.h"
#include <fcntl.h>


int	main()
{
	int	target_fd;

	target_fd = open("./short_target", O_RDONLY);
	printf("gnl result: %s", get_next_line(target_fd));
	return (0);
}
