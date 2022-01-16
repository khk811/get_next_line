#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# include <stdlib.h>
# include <unistd.h>

typedef struct	s_list
{
	int	fd;
	char	*buf;
	struct s_list	*next;
}	t_list;

char	*get_next_line(int fd);
char	*alloc_arr(char **arr, int size);
void	*ft_memset(void *b, int c, int len);
void	*ft_memmove(void *dst, void *src, int len);
t_list	*create_element(int fd);
int		ft_strlen(char *s);

#endif
