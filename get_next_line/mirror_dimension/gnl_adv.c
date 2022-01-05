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

	new = malloc(sizeof(t_list));
	if (!new)
		return ;
	new->content = content;
	new->next = NULL;
	if (*lst)
		printf("*lst: %s\n", (*lst)->content);
	printf("new: %s\n", new->content);
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	last = ft_lstlast(*lst);
	last->next = new;
}

static void	ft_lst_print(t_list **lst)
{
	t_list	*tmp;

	tmp = *lst;
	while (tmp)
	{
		if (!tmp)
			return ;
		printf("**element: %s\n", tmp->content);
		tmp = tmp->next;
	}
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

	if (lst)
		printf("***%s\n", lst->content);
	read_int = read(fd, buf, BUFFER_SIZE);
	if (read_int == -1 || read_int == 0)
		return (NULL);
	printf("read is done\n");
	if (lst)
		printf("--->%s\n", lst->content);
	ft_gnl_lst(&lst, buf);
	printf("=========%s\n", lst->content);
	/*
	if (!ft_check_newline(&lst))
		return (NULL);
		*/
	ft_lst_print(&lst);
	printf(">>>>>>>>>>>>>>>>%s\n", lst->content);
	printf("\n\n");
	return (NULL);
}
