/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wooseoki <wooseoki@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 19:39:21 by wooseoki          #+#    #+#             */
/*   Updated: 2023/03/27 14:08:00 by wooseoki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

void	free_stack(t_stack *stack)
{
	t_stack	*temp;
	t_stack	*node;

	node = stack;
	while (node)
	{
		temp = node;
		free(temp);
		node = node->next;
	}
}

t_list	*parse_subshell(t_list *node, t_fptr **parse_table)
{
	t_stack	*stack;
	int		accept;

	stack = NULL;
	node = node->next;
	parse_table[REDIRECTION][0] = &shift_r_command;
	while (node && node->type != SUBS_CLOSE)
	{
		push_stack(&stack, node->type);
		reduce_token(parse_table, &stack);
		node = node->next;
		if (node == NULL)
		{
			parse_table[REDIRECTION][0] = NULL;
			free_stack(stack);
			return (NULL);
		}
	}
	accept = repeat_reduce_shift(parse_table, &stack, 1);
	parse_table[REDIRECTION][0] = NULL;
	free_stack(stack);
	if (accept == FALSE)
		return (NULL);
	node->type = SUBSHELL;
	return (node);
}

int	check_accept(t_fptr **parse_table, t_stack *stack)
{
	int	accept;

	accept = repeat_reduce_shift(parse_table, &stack, 1);
	if (accept == FALSE)
	{
		set_subshell_function(parse_table);
		accept = repeat_reduce_shift(parse_table, &stack, 1);
	}
	free_stack_table(stack, parse_table);
	return (accept);
}

int	parse_token(t_list **token_list)
{
	t_fptr	**parse_table;
	t_stack	*stack;
	t_list	*node;

	parse_table = init_parse_table();
	stack = NULL;
	node = *token_list;
	node = *token_list;
	while (node)
	{
		if (node->type == SUBS_OPEN)
		{
			node = parse_subshell(node, parse_table);
			if (node == NULL)
			{
				free_stack_table(stack, parse_table);
				return (FALSE);
			}
		}
		push_stack(&stack, node->type);
		reduce_token(parse_table, &stack);
		node = node->next;
	}
	return (check_accept(parse_table, stack));
}
