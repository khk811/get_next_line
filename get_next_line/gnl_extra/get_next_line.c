#include "get_next_line.h"
#include <stdio.h>

/*
static size_t	ft_strlen(char *s)
{
	char	*end;

	end = *s;
	while (*end)
		end++;
	return (end - s);
}

static void	*ft_memmove(void *dst, void *src, size_t len)
{
	size_t	i;

	i = 0;
	if (dst < src)
	{
		while (i < len)
		{
			*(unsigned char *)(dst + i) = *(unsigned char *)(src + i);
			i++;
		}
		else if (dst < src)
		{
			while (len-- > 0)
				*(unsigned char *)(dst + len) = *(unsigned char *)(src + len);
		}
		return (dst);
}*/

static int	ft_lstfind_fd(t_list **lst, int fd)
{
	int	ret;
	t_list	*tmp;

	ret = 0;
	tmp = *lst;
	while (tmp)
	{
		if (tmp->fd == fd)
			ret++;
		tmp = tmp->next;
	}
	return (ret);
}

char	*get_next_line(int fd)
{
	static t_list	*lst;
	char	*buf;
	char	*result;
	int read_result;

	if (BUFFER_SIZE <= 0 || fd < 0)
		return (NULL);
	buf = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	read_result = read(fd, buf, BUFFER_SIZE);
	if (read_result <= 0)
		ft_free_char(&buf);
	buf[read_result] = '\0';
	if (!ft_strchr(buf, 10))
		ft_lstadd_back(&lst, ft_lstnew(fd, buf));
	return (buf);
}
