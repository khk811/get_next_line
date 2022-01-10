#include "get_next_line.h"

int	ft_strlen(char *s)
{
	int	i;
	
	i = 0;
	while (s[i])
		i++;
	return (i);
}

char *ft_strncat(char *dst, char *src, int n)
{
    int i;
    int j;

    i = ft_strlen(dst);
    j = 0;
    while (src[j] && j < n)
    {
        dst[i] = src[j];
        i++;
        j++;
    }
    dst[i] = '\0';
    return (dst);
}

int	cnt_wo_head(t_list **lst)
{
	t_list	*tmp;
	int	i;

    i = 0;
    tmp = *lst;
	while (tmp->next)
	{
		tmp = tmp->next;
        i++;
	}
	return (i);
}

t_list	*create_element(char *content)
{
	t_list	*new;
	char	*new_content;

	new = malloc(sizeof(t_list));
	if (!new)
		return (NULL);
	new_content = (char *)malloc(sizeof(char) * (ft_strlen(content) + 1));
	ft_strncat(new_content, content, ft_strlen(content) + 1);
	new->content = new_content;
	new->next = NULL;
	return (new);
}

void	add_element(t_list **lst, t_list *new)
{
	t_list	*tmp;

	tmp = *lst;
	if (!*lst)
		*lst = new;
	else
	{
		while (tmp->next)
            tmp = tmp->next;
        tmp->next = new;
	}
}

void ft_lstclear(t_list **lst)
{
    t_list  *next_element;

    while (*lst)
    {
        next_element = (*lst)->next;
        free((*lst)->content);
        *lst = next_element;
    }
}
