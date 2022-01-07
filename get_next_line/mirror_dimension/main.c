#include <stdio.h>
#include "gnl.h"
#include <fcntl.h>

int	main()
{
	int	target_fd;
	int	i;
	char	*result;

	i = 0;
	target_fd = open("./read_fd_target", O_RDONLY);
	while (i++ < 10)
	{
		//printf("\n(%d)\n"s, i);
		result = get_next_line(target_fd);
		if (result)
			printf("%s", result);
	}
	return (0);
}
