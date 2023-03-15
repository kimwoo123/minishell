/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chajung <chajung@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 10:42:51 by chajung           #+#    #+#             */
/*   Updated: 2023/03/14 10:42:52 by chajung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// make_nodes_a_stack
static void	print_list(t_list **node)
{
	t_list	*temp;

	temp = *node;
	while (temp)
	{
		printf("type: %d, content: %s\n", temp->type, temp->content);
		temp = temp->next;
	}
}

int	test_code(t_list **node)
{
	t_list	*temp;

	temp = *node;
	while (temp)
	{
		printf("%d: %s\n", temp->type, temp->content);
		temp = temp->next;
	}
	return (0);
}
