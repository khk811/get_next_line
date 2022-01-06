#include "gnl.h"
#include <stdio.h>

static void	*ft_memcpy(void *dst, void *src, size_t n)
{
	size_t	i;

	if (!dst && !src)
		return (NULL);
	i = 0;
	while (i < n)
	{
		*(unsigned char *)(dst + i) = *(unsigned char *)(src + i);
		i++;
	}
	return (dst);
}

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
	char	*str;

	new = malloc(sizeof(t_list));
	str = (char *)malloc(sizeof(char) * (BUFFER_SIZE));
	if (!new)
		return ;
	ft_memcpy(str, content, BUFFER_SIZE);
	new->content = str;
	new->next = NULL;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	last = ft_lstlast(*lst);
	last->next = new;
}

static int	ft_check_read(int n)
{
	if (n == -1 || n == 0)
		return (0);
	else
		return (1);
}

static void	ft_print_lst(t_list	**lst)
{
	t_list	*tmp;
	char	*content;

	tmp = *lst;
	while (tmp)
	{
		content = tmp->content;
		while (*content && *content != '\n')
		{
			write(1, content, 1);
			content++;
		}
		if (!tmp->next)
			break ;
		tmp = tmp->next;
	}
	write(1, "**\n", 3);
	*lst = NULL;
}

static void	ft_check_newline(t_list **lst)
{
	t_list	*tmp;
	char	*content;

	tmp = *lst;
	while (tmp->next)
	{
		content = tmp->content;
		while (*content)
		{
			if (*content == '\n')
			{
				ft_print_lst(lst);
				return ;
			}
			content++;
		}
		if (!tmp->next)
			break ;
		tmp = tmp->next;
	}
}

char	*get_next_line(int fd)
{
	char	buf[BUFFER_SIZE];
	//char	*result;
	static t_list	*lst = NULL;

	if (!ft_check_read(read(fd, buf, BUFFER_SIZE)))
		return (NULL);
	if (!lst)
		printf("(lst = null)\n");
	ft_gnl_lst(&lst, buf);
	ft_check_newline(&lst);
	return (NULL);
}
