/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shift_rule.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wooseoki <wooseoki@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 15:26:40 by wooseoki          #+#    #+#             */
/*   Updated: 2023/03/26 14:02:40 by wooseoki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell_bonus.h"

int	shift_command(t_stack **stack_node)
{
	t_stack	*ct_node;

	ct_node = (*stack_node)->next;
	ct_node->type = COMMAND;
	return (SUCCESS);
}

int	shift_r_command(t_stack **stack_node)
{
	(*stack_node)->type = COMMAND;
	return (SUCCESS);
}

int	shift_ct_command(t_stack **stack_node)
{
	(*stack_node)->type = COMMAND;
	return (SUCCESS);
}

int	shift_w_ct(t_stack **stack_node)
{
	(*stack_node)->type = CMD_TOKEN;
	return (SUCCESS);
}

int	shift_s_cmd(t_stack **stack_node)
{
	(*stack_node)->type = SUBS_CMD;
	return (SUCCESS);
}
