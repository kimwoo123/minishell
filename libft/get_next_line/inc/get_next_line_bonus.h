/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wooseoki <wooseoki@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 18:19:04 by wooseoki          #+#    #+#             */
/*   Updated: 2022/12/22 17:42:04 by wooseoki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# include <unistd.h>
# include <stdlib.h>

typedef struct s_fdlist
{
	int				fd;
	char			*strg;
	struct s_fdlist	*next;
	struct s_fdlist	*prev;
}	t_fdlist;

int			ft_strchr(char *str, int c);
int			read_file(int fd, t_fdlist *node);
char		*ft_substr(char *str, size_t start, size_t len);
char		*ft_strjoin(char *s1, char *s2);
char		*seperate_str(t_fdlist *node);
char		*get_next_line(int fd);
size_t		ft_strlen(char *str);
void		free_node(t_fdlist **head, t_fdlist *node);
t_fdlist	*ft_lstnew(t_fdlist *prev_node, int fd);
t_fdlist	*find_node(t_fdlist *node, int fd);

#endif
