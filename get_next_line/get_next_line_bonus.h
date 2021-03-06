/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunkkim <hyunkkim@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 14:41:03 by hyunkkim          #+#    #+#             */
/*   Updated: 2022/01/21 14:41:05 by hyunkkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# include <stdlib.h>
# include <unistd.h>

typedef struct s_list
{
	         int	fd;
	        char	*buf;
	struct s_list	*next;
}	t_list;

char	*get_next_line(int fd);
char	*alloc_arr(char **arr, int size);
void	*ft_memset(void *b, int c, int len);
void	*ft_memmove(void *dst, void *src, int len);
int		valid_read(int fd, char **buf);
int		ft_strlen(char *s);

#endif
