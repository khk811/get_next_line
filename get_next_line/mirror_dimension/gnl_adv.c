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
		printf("[new!!]\n");
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

static char	*ft_ret_line(t_list **lst, char *result, int len)
{
	int	i;
	t_list	*tmp;
	char	*content;

	i = 0;
	tmp = *lst;
	while (tmp && i < len)
	{
		content = tmp->content;
		while (*content)
		{
			if (*content == '\n')
				break ;
			result[i] = *content;
			i++;
			content++;
		}
		if (!tmp->next)
			break ;
		tmp = tmp->next;
	}
	result[i] = '\0';
	return (result);
}

static char *ft_check_newline(t_list **lst, char *result)
{
	t_list	*tmp;
	char	*content;
	int	i;

	tmp = *lst;
	i = 0;
	while (tmp)
	{
		content = tmp->content;
		while (*content)
		{
			if (*content == '\n')
			{
				result = (char *)malloc(sizeof(char) * (i + 1));
				if (!result)
					printf("I can't");
				ft_ret_line(lst, result, i);
				*lst = NULL;
				return (result);
			}
			i++;
			content++;
		}
		if (!tmp->next)
			break ;
		tmp = tmp->next;
	}
	return (NULL);
}

char	*get_next_line(int fd)
{
	char	buf[BUFFER_SIZE];
	char	*result;
	static t_list	*lst = NULL;

	result = NULL;
	if (!ft_check_read(read(fd, buf, BUFFER_SIZE)))
		return (NULL);
	ft_gnl_lst(&lst, buf);
	result = ft_check_newline(&lst, result);
	return (result);
}
