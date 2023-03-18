/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wooseoki <wooseoki@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 15:24:20 by wooseoki          #+#    #+#             */
/*   Updated: 2023/03/18 15:03:02 by wooseoki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

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

void	free_stack_table(t_stack *stack, t_fptr **table)
{
	t_stack *temp;
	t_stack *node;
	size_t	index;

	node = stack;
	while (node)
	{
		temp = node->next;
		free(node);
		node = temp;
	}
	index = 0;
	while (index < PIPE + 1)
	{
		free(table[index]);
		++index;
	}
	free(table);
}
