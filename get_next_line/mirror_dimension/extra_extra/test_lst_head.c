#include <stdio.h>
#include <stdlib.h>

typedef struct	s_list
{
	int	fd;
	char	*content;
	struct s_list	*next;
}	t_list;

t_list	*create_element(int fd, char *content)
{
	t_list	*new;

	new = malloc(sizeof(t_list));
	if (!new)
		return (NULL);
	else
	{
		new->fd = fd;
		new->content = content;
		new->next = NULL;
	}
	return (new);
}

t_list	*find_fd(int fd, t_list **lst, char *content)
{
	t_list	*tmp;

	tmp = *lst;
	if (!*lst)
	{
		*lst = create_element(fd, content);
		return (tmp);
	}
	while (tmp && tmp->next)
	{
		if (tmp->fd == fd)
			break;
		tmp = tmp->next;
	}
	if (tmp->fd != fd)
	{
		tmp->next = create_element(fd, content);
		tmp = tmp->next;
	}
	return (tmp);
}

void	rm_element(t_list **lst, int fd)
{
	t_list	*before;
	t_list	*tmp;

	before = NULL;
	tmp = *lst;
	if (!tmp)
		return ;
	while (tmp->next)
	{
		if (tmp->fd != fd)
			before = tmp;
		if (tmp->fd == fd)
			break ;
		tmp = tmp->next;
	}
	if (before)
	{
		printf("before target - fd: %d content: %s\n", before->fd, before->content);
		before->next = tmp->next;
	}
	if (tmp->fd == fd)
		printf("rm target - fd: %d content: %s\n", tmp->fd, tmp->content);
	else if (tmp->fd != fd)
		printf("couldn't find target\n");
}
/*
void	ft_lstadd_back(t_list **head, t_list *new)
{
	t_list	*last;

	last = *head;
	while (last)
	{
		if (!(last)->next)
			break;
		last = (last)->next;
	}
	(last)->next = new;
}*/

int	main(void)
{
	t_list	*head = NULL;
	t_list	*fd_3 = NULL;
	t_list	*fd_4 = NULL;
	t_list	*fd_5 = NULL;
	t_list	*fd_6 = NULL;
	t_list	*fd_13 = NULL;

	fd_3 = find_fd(3, &head, "AAAA");
	fd_4 = find_fd(4, &head, "BBBB");
	fd_5 = find_fd(5, &head, "CCCC");
	fd_6 = find_fd(6, &head, "DDDD");
	fd_13 = find_fd(13, &head, "EEEE");
	//printf("the curr head content: %s\n\n", head->content);
	if (!head)
		printf("empty head\n");
	printf("fd_5 content: %s\n", fd_5->content);
	rm_element(&head, 4);
	
	while (head->next)
	{
		printf("the content: %s\n", head->content);
		head = head->next;
	}
	printf("the last content: %s\n", head->content);
	return (0);
}
