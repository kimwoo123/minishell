/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wooseoki <wooseoki@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 15:24:20 by wooseoki          #+#    #+#             */
/*   Updated: 2023/03/20 16:59:29 by wooseoki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

void	free_list(t_list **list)
{
	t_list	*node;
	t_list	*temp;

	node = *list;
	while (node)
	{
		temp = node->next;
		free(node->content);
		node->content = NULL;
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
	t_stack	*temp;
	t_stack	*node;
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

void	free_tree(t_tree *node)
{
	if (node == NULL)
		return ;
	free_tree(node->left);
	free_tree(node->right);
	if (node->content)
		free(node->content);
	free(node);
	node = NULL;
}

void	free_double_array(char **array)
{
	int	i;

	if (array == NULL)
		return ;
	i = 0;
	while (array[i])
	{
		if (array[i] != NULL)
			free(array[i]);
		array[i] = NULL;
		i++;
	}
	if (array != NULL)
		free(array);
	array = NULL;
}
