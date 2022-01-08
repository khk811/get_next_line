#include "get_next_line.h"
#include <stdio.h>

static int	ft_strlen(char *s)
{
	int	i;
	
	i = 0;
	while (s[i])
		i++;
	return (i);
}

static void	*ft_memcpy(void *dst, void *src, int n)
{
	int	i;

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

static char	*read_for_gnl(int fd, char **buf)
{
    int read_result;

    read_result = 0;
	*buf = (char *)malloc(sizeof(char) * (BUFFER_SIZE));
    read_result = read(fd, *buf, BUFFER_SIZE);
    if (read_result == 0 || read_result == -1)
        return (NULL);
    return (*buf);
}

static t_list	*create_element(char *content)
{
	t_list	*new;
	char	*new_content;

	new = malloc(sizeof(t_list));
	if (!new)
		return (NULL);
	new_content = (char *)malloc(sizeof(char) * ft_strlen(content));
	ft_memcpy(new_content, content, ft_strlen(content));
	new->content = new_content;
	new->next = NULL;
	return (new);
}

static void	add_element(t_list **lst, t_list *new)
{
	t_list	*tmp;

	tmp = *lst;
	if (!*lst)
		*lst = new;
	else
	{
		while (tmp->next)
			tmp = tmp->next;
		new = tmp->next;
	}
}

static void	check_newline(char *buf, t_list **lst)
{
	int	i;

	i = 0;
	while (buf[i])
	{
		if (buf[i] == '\n')
		{
			printf("found newline in buf\n");
			return ;
		}
		i++;
	}
	printf("newline undetected\n");
	add_element(lst, create_element(buf));
}

char *get_next_line(int fd)
{
    //char    *result;
    char    *buf;
	static t_list	*lst;

    buf = NULL;
	lst = NULL;
    //result = NULL;
    if (BUFFER_SIZE <= 0)
        return (NULL);
	if (!read_for_gnl(fd, &buf))
		return (NULL);
	check_newline(buf, &lst);
	if (lst)
		printf("head content: %s\n", lst->content);
    return (buf);
}
