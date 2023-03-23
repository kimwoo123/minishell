/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wooseoki <wooseoki@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 15:25:25 by wooseoki          #+#    #+#             */
/*   Updated: 2023/03/22 09:06:11 by wooseoki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

t_stack	*create_elem(int type)
{
	t_stack	*elem;

	elem = (t_stack *)malloc(sizeof(t_stack));
	if (elem == NULL)
		return (NULL);
	elem->type = type;
	elem->next = NULL;
	return (elem);
}

int	pop_stack(t_stack **stack)
{
	t_stack	*node;
	int		ret;

	if (*stack == NULL)
		return (FAILURE);
	ret = (*stack)->type;
	node = *stack;
	*stack = (*stack)->next;
	free(node);
	return (ret);
}

void	push_stack(t_stack **stack, int type)
{
	t_stack	*node;

	node = create_elem(type);
	if (node == NULL)
		return ;
	node->next = *stack;
	*stack = node;
}
