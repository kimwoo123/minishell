/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chajung <chajung@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 10:42:51 by chajung           #+#    #+#             */
/*   Updated: 2023/03/19 09:29:03 by wooseoki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	shift_token(t_fptr **parse_table, t_stack **stack_node)
{
	int	s_type;

	if ((*stack_node) != NULL)
	{
		s_type = (*stack_node)->type;
		if (parse_table[s_type][0])
		{
			parse_table[s_type][0](stack_node);
			return (TRUE);
		}
	}
	return (FALSE);
}

int	reduce_token(t_fptr **parse_table, t_stack **stack_node)
{
	int	s_type;
	int	ns_type;

	if ((*stack_node) != NULL && (*stack_node)->next != NULL)
	{
		s_type = (*stack_node)->type;
		ns_type = (*stack_node)->next->type;
		if (parse_table[ns_type][s_type])
		{
			parse_table[ns_type][s_type](stack_node);
			return (TRUE);
		}
	}
	return (FALSE);
}

int	repeat_reduce_shift(t_fptr **parse_table, t_stack **stack)
{
	t_stack	*s_node;
	size_t	ret;

	while (1)
	{
		ret = 0;
		s_node = *stack;
		while (s_node)
		{
			ret += reduce_token(parse_table, &s_node);
			if (ret)
				break ;
			ret += shift_token(parse_table, &s_node);
			if (ret)
				break ;
			s_node = s_node->next;
		}
		if (ret == 0)
			break ;
	}
	if ((*stack && (*stack)->next == NULL) && (*stack)->type == COMMAND)
		return (TRUE);
	return (FALSE);
}

int	parse_token(t_list **token_list)
{
	t_fptr	**parse_table;
	t_stack	*stack;
	t_list	*node;
	int		accept;

	parse_table = init_parse_table();
	stack = NULL;
	node = *token_list;
	while (node)
	{
		push_stack(&stack, node->type);
		if (node->type == ZERO)
		{
			free_stack_table(stack, parse_table);
			return (FALSE);
		}
		reduce_token(parse_table, &stack);
		node = node->next;
	}
	accept = repeat_reduce_shift(parse_table, &stack);
	free_stack_table(stack, parse_table);
	if (accept == FALSE)
		return (FALSE);
	return (TRUE);
}

int	check_syntax(t_list **token_list)
{
	int		accept;

	if (*token_list == NULL)
		return (TRUE);
	accept = parse_token(token_list);
	if (accept == FALSE)
	{
		printf("syntax error\n");
		return (FALSE);
	}
	printf("syntax fine\n");
	return (TRUE);
}
