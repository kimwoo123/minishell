/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reduce_rule.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wooseoki <wooseoki@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 15:26:09 by wooseoki          #+#    #+#             */
/*   Updated: 2023/03/25 17:02:38 by wooseoki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell_bonus.h"

int	reduce_redirection(t_stack **stack_node)
{
	t_stack	*next_node;

	next_node = (*stack_node)->next;
	(*stack_node)->next = next_node->next;
	pop_stack(&next_node);
	(*stack_node)->type = REDIRECTION;
	return (SUCCESS);
}

int	reduce_cmd_token(t_stack **stack_node)
{
	t_stack	*next_node;

	next_node = (*stack_node)->next;
	(*stack_node)->next = next_node->next;
	pop_stack(&next_node);
	(*stack_node)->type = CMD_TOKEN;
	return (SUCCESS);
}

int	reduce_command(t_stack **stack_node)
{
	t_stack	*next_node;

	next_node = (*stack_node)->next;
	(*stack_node)->next = next_node->next;
	pop_stack(&next_node);
	(*stack_node)->type = COMMAND;
	return (SUCCESS);
}

int	reduce_pipe_command(t_stack **stack_node)
{
	t_stack	*next_node;

	next_node = (*stack_node)->next;
	(*stack_node)->next = next_node->next;
	pop_stack(&next_node);
	(*stack_node)->type = PIPE_CMD;
	return (SUCCESS);
}

int	reduce_group_command(t_stack **stack_node)
{
	t_stack	*next_node;

	next_node = (*stack_node)->next;
	(*stack_node)->next = next_node->next;
	pop_stack(&next_node);
	(*stack_node)->type = GROUP_CMD;
	return (SUCCESS);
}
