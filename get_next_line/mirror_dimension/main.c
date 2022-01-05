#include <stdio.h>
#include "gnl.h"
#include <fcntl.h>

int	main()
{
	int	target_fd;
	int	i;

	i = 0;
	target_fd = open("./short_target", O_RDONLY);
	while (i++ < 5)
		get_next_line(target_fd);
	return (0);
}
