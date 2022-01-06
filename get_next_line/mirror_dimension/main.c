#include <stdio.h>
#include "gnl.h"
#include <fcntl.h>

int	main()
{
	int	target_fd;
	int	i;
	char	*result;

	i = 0;
	target_fd = open("./short_target", O_RDONLY);
	while (i++ < 20)
	{
		printf("\n(%d)\n", i);
		result = get_next_line(target_fd);
		if (result)
		{
			printf("%s", result);
			printf("<<Thank U, Next>>\n");
		}
	}
	return (0);
}
