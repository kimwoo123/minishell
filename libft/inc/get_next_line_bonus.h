/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chajung <chajung@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 20:35:42 by chajung           #+#    #+#             */
/*   Updated: 2022/11/24 20:35:49 by chajung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# include <unistd.h>
# include <stdlib.h>
# include "libft.h"

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1024
# endif

typedef struct s_node
{
	int				fd;
	char			*backup;
	struct s_node	*next;
}	t_node;

void	clear_node(t_node **head, t_node *node);
t_node	*find_node(t_node **head, int fd);
char	*clean_up(char *line);
char	*read_line(char *backup, int fd);
char	*get_next_line(int fd);

#endif
