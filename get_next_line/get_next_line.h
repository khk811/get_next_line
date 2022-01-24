/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunkkim <hyunkkim@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 14:36:34 by hyunkkim          #+#    #+#             */
/*   Updated: 2022/01/21 14:36:36 by hyunkkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>

char	*get_next_line(int fd);
char	*alloc_arr(char **arr, int size);
void	*ft_memset(void *b, int c, int len);
void	*ft_memmove(void *dst, void *src, int len);
int		valid_read(int fd, char **buf);
int		ft_strlen(char *s);

#endif
