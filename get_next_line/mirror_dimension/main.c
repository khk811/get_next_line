#include <stdio.h>
#include "get_next_line.h"
#include <fcntl.h>


int	main()
{
	int	target_fd;
	int	i;
	t_list	*head;
	t_list	element2 = {"BBBB", NULL};
	t_list	element1 = {"AAAA", &element2};
	t_list	element3 = {"CCCC", NULL};

	i = 0;
	target_fd = open("./short_target", O_RDONLY);
	printf("gnl result: %s", get_next_line(target_fd));
	head = &element1;
	add_element(&head, &element3);
	printf("\n =====%s\n", head->next->content);
	while (head->next)
	{
		printf("##%s\n", head->content);
		head = head->next;
	}
	return (0);
}
