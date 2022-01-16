#include "get_next_line_bonus.h"

int	ft_strlen(char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

void	*ft_memset(void *b, int c, int len)
{
	int	i;

	i = 0;
	while (i < len)
		*(unsigned char *)(b + (i++)) = (unsigned char)c;
	return ((void *)b);
}

void	*ft_memmove(void *dst, void *src, int len)
{
	int	i;

	i = 0;
	if (dst < src)
	{
		while (i < len)
		{
			*(unsigned char *)(dst + i) = *(unsigned char *)(src + i);
			i++;
		}
	}
	else if (dst > src)
	{
		while (len-- > 0)
			*(unsigned char *)(dst + len) = *(unsigned char *)(src + len);
	}
	return ((void *)dst);
}

char	*alloc_arr(char **arr, int size)
{
	char	*tmp;

	tmp = NULL;
	if (!*arr)
	{
		*arr = (char *)malloc(sizeof(char) * (size + 1));
		if (!*arr)
			return (NULL);
		ft_memset(*arr, 0, size + 1);
	}
	else if (*arr)
	{
		tmp = (char *)malloc(sizeof(char) * (ft_strlen(*arr) + 1));
		if (!tmp)
			return (NULL);
		ft_memmove(tmp, *arr, ft_strlen(*arr) + 1);
		free(*arr);
		*arr = (char *)malloc(sizeof(char) * (ft_strlen(tmp) + size + 1));
		if (!*arr)
			return (NULL);
		ft_memset(*arr, 0, ft_strlen(tmp) + size + 1);
		ft_memmove(*arr, tmp, ft_strlen(tmp) + 1);
		free(tmp);
	}
	return (*arr);
}

t_list	*create_element(int fd)
{
	t_list	*new;

	new = malloc(sizeof(t_list));
	if (!new)
		return (NULL);
	else
	{
		new->fd = fd;
		new->buf = NULL;
		new->next = NULL;
	}
	return (new);
}
