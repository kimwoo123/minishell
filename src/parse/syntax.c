/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chajung <chajung@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 10:42:51 by chajung           #+#    #+#             */
/*   Updated: 2023/03/18 17:11:47 by wooseoki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// make_nodes_a_stack

int	shift_token(t_fptr **reduce_table, t_stack **stack_node)
{
	int	s_type;

	if ((*stack_node) != NULL)
	{
		s_type = (*stack_node)->type;
		if (reduce_table[s_type][0])
		{
			reduce_table[s_type][0](stack_node);
			return (TRUE);
		}
	}
	return (FALSE);
}

int	reduce_token(t_fptr **reduce_table, t_stack **stack_node)
{
	int	s_type;
	int	ns_type;

	if ((*stack_node) != NULL && (*stack_node)->next != NULL)
	{
		s_type = (*stack_node)->type;
		ns_type = (*stack_node)->next->type;
		if (reduce_table[ns_type][s_type])
		{
			reduce_table[ns_type][s_type](stack_node);
			return (TRUE);
		}
	}
	return (FALSE);
}

int	repeat_reduce_shift(t_fptr **reduce_table, t_stack **stack)
{
	t_stack	*s_node;
	size_t	ret;

	while (1)
	{
		ret = 0;
		s_node = *stack;
		while (s_node)
		{
			ret += reduce_token(reduce_table, &s_node);
			if (ret)
				break ;
			ret += shift_token(reduce_table, &s_node);
			if (ret)
				break ;
			s_node = s_node->next;
		}
		if (ret == 0)
			break ;
	}
	if ((*stack && (*stack)->next == NULL) && (*stack)->type == COMMAND)
		return (FALSE);
	return (TRUE);
}

int	test_code(t_list **node)
{
	t_stack	*stack;
	t_list	*temp;
	t_fptr	**reduce_table;
	int		syntax_error;

	if (*node == NULL)
		return (FALSE);
	reduce_table = init_reduce_functions();
	stack = NULL;
	temp = *node;
	while (temp)
	{
		push_stack(&stack, temp->type);
		reduce_token(reduce_table, &stack);
		temp = temp->next;
	}
	syntax_error = repeat_reduce_shift(reduce_table, &stack);
	free_stack_table(stack, reduce_table);
	if (syntax_error == 1)
		return (FALSE);
	return (TRUE);
}
