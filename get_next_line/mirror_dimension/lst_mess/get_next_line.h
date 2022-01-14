#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

#include <unistd.h>
#include <stdlib.h>

typedef struct	s_list
{
	int	fd;
	int	is_nl;
	void	*content;
	struct s_list	*next;
}	t_list;

char	*get_next_line(int fd);
t_list	*last_ele(t_list **lst);
int	ft_strlen(char *s);
char	*ft_strncat(char *dst, char *src, int len);
t_list	*create_element(int fd, int nl_eof, char *content);
void	add_element(t_list **lst, t_list *new);

#endif
