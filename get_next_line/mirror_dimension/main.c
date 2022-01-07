#include <stdio.h>
#include "get_next_line.h"
#include <fcntl.h>

int	main()
{
	int	target_fd;
	int	i;
	char	*result;

	i = 0;
	target_fd = open("./short_target", O_RDONLY);
	result = get_next_line(target_fd);
    printf("%s", result);
	return (0);
}
