#include "gnl.h"
#include <stdio.h>

static t_list	*ft_lstlast(t_list *lst)
{
	while (lst)
	{
		if (!lst->next)
			return (lst);
		lst = lst->next;
	}
	return (NULL);
}

static void	ft_gnl_lst(t_list **lst, void *content)
{
	t_list	*new;
	t_list	*last;

	if (*lst)
		printf("lst: %s\n", (*lst)->content);
	new = malloc(sizeof(t_list));
	if (!new)
		return ;
	new->content = content;
	new->next = NULL;
	if (!*lst)
	{
		*lst = new;
		printf("add new element: %s\n", (*lst)->content);
		return ;
	}
	last = ft_lstlast(*lst);
	printf("last: %s\n", last->content);
	printf("lst: %s\n", (*lst)->content);
	last->next = new;
}
/*
static t_list	*ft_check_newline(t_list **lst)
{
	char	*content;

	while ((*lst)->next)
	{
		content = (*lst)->content;
		while (*content)
		{
			if (*content == '\n')
				return (*lst);
			content++;
		}
		if (!(*lst)->next)
			break ;
		*lst = (*lst)->next;
	}
	return (NULL);
}
*/
char	*get_next_line(int fd)
{
	char	buf[BUFFER_SIZE];
	//char	*result;
	static t_list	*lst = NULL;
	int	read_int;

	read_int = read(fd, buf, BUFFER_SIZE);
	if (read_int == -1 || read_int == 0)
		return (NULL);
	printf("read is done\n");
	ft_gnl_lst(&lst, buf);
	/*
	if (!ft_check_newline(&lst))
		return (NULL);
		*/
	if (lst->content)
		printf("lst result: %s\n", lst->content);
	else
		printf("???\n");
	printf("\n\n");
	return (NULL);
}
