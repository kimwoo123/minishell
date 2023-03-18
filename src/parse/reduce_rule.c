/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reduce_rule.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wooseoki <wooseoki@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 15:26:09 by wooseoki          #+#    #+#             */
/*   Updated: 2023/03/18 15:26:35 by wooseoki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	reduce_redirection(t_stack **stack_node) // r W / R R
{
	t_stack *next_node;

	next_node = (*stack_node)->next;
	(*stack_node)->next = next_node->next;
	pop_stack(&next_node);
	(*stack_node)->type = REDIRECTION;
	return (SUCCESS);
}

int	reduce_cmd_token(t_stack **stack_node) // C W
{
	t_stack *next_node;

	next_node = (*stack_node)->next;
	(*stack_node)->next = next_node->next;
	pop_stack(&next_node);
	(*stack_node)->type = CMD_TOKEN;

	return (SUCCESS);
}

int	reduce_command(t_stack **stack_node) // C C
{
	t_stack *next_node;

	next_node = (*stack_node)->next;
	(*stack_node)->next = next_node->next;
	pop_stack(&next_node);
	(*stack_node)->type = COMMAND;
	return (SUCCESS);
}

int	reduce_pipe_command(t_stack **stack_node) // SP SP
{
	t_stack *next_node;

	next_node = (*stack_node)->next;
	(*stack_node)->next = next_node->next;
	pop_stack(&next_node);
	(*stack_node)->type = PIPE_CMD;
	return (SUCCESS);
}

int	reduce_group_command(t_stack **stack_node) // S S / SP P
{
	t_stack *next_node;

	next_node = (*stack_node)->next;
	(*stack_node)->next = next_node->next;
	pop_stack(&next_node);
	(*stack_node)->type = GROUP_CMD;
	return (SUCCESS);
}
