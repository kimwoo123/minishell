/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wooseoki <wooseoki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 15:24:20 by wooseoki          #+#    #+#             */
/*   Updated: 2023/03/12 18:44:43 by wooseoki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_list(t_list **list)
{
	t_list	*node;
	t_list	*temp;

    node = *list;
	while (node)
	{
		temp = node->next;
		free(node->content);
		free(node);
		node = temp;
	}
}

void	free_double(char **str)
{
	size_t	index;

	index = 0;
	while (str[index])
	{
		if (str[index])
			free(str[index]);
		++index;
	}
	if (str)
		free(str);
}
