#include "get_next_line.h"

void	ft_free_char(char **s)
{
	if (!*s)
		return ;
	else if (*s)
		free(*s);
	*s = NULL;
}

char	*ft_strchr(char *s, int c)
{
	char	char_c;

	char_c = (char)c;
	if (!char_c)
	{
		while (*s)
			s++;
		return ((char *)s);
	}
	while (*s)
	{
		if (*s == char_c)
			return ((char *)s);
		s++;
	}
	return (NULL);
}

t_list	*ft_lstnew(int fd, void *buf)
{
	t_list	*new;

	new = malloc(sizeof(t_list));
	if (!new)
		return (NULL);
	else
	{
		new->fd = fd;
		new->buf = buf;
		new->next = NULL;
	}
	return (new);
}

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*tmp;

	if (!lst || !new)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	tmp = *lst;
	while (tmp)
	{
		if (!tmp->next)
			break ;
		tmp = tmp->next;
	}
	tmp->next = new;
}
/*
void	ft_lstdel_fd(t_list **lst, int fd)
{
	t_list	*tmp;

	if (!lst || !*lst)
		return ;
	tmp = *lst;
	while (tmp)
	{
		if (!tmp->next)
			break ;
		if (tmp->fd == fd)
		{
			ft_free_char(tmp->buf);
			free(tmp);
			tmp = NULL;
		}
		tmp = tmp->next;
	}
	ft_free_char(tmp->buf);
	free(tmp);
	tmp = NULL;
}*/
