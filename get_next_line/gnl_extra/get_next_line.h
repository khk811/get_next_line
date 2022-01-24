#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

#include <unistd.h>
#include <stdlib.h>

typedef struct s_list
{
	int	fd;
	char	*buf;
	struct s_list	*next;
}	t_list;

char	*get_next_line(int fd);
void	ft_free_char(char **s);
char	*ft_strchr(char *s, int c);
void	ft_lstadd_back(t_list **lst, t_list *new);
t_list	*ft_lstnew(int fd, void *buf);

#endif
