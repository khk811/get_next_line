#include <stdio.h>
#include <stdlib.h>

typedef struct	s_list
{
	void	*content;
	struct s_list	*next;
}	t_list;

t_list	*ft_lstlast(t_list *lst)
{
	while (lst)
	{
		if (!lst->next)
			return (lst);
		lst = lst->next;
	}
	return (NULL);
}

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*last;

	if (!*lst)
	{
		*lst = new;
		return ;
	}
	last = ft_lstlast(*lst);
	last->next = new;
	return ;
}

void	ft_lst_print(t_list **lst)
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

int	main()
{
	t_list	*head;
	t_list	ele2 = {"B", NULL};
	t_list	ele1 = {"A", &ele2};
	t_list	ele3 = {"C", NULL};
	t_list	ele4 = {"D", NULL};

	head = &ele1;
	ft_lstadd_back(&head, &ele3);
	printf("head: %s\n", head->content);
	ft_lst_print(&head);
	ft_lstadd_back(&head, &ele4);
	printf("head: %s\n", head->content);
	ft_lst_print(&head);
	return (0);
}
