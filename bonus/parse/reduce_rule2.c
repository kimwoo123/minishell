/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reduce_rule2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wooseoki <wooseoki@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 18:29:01 by wooseoki          #+#    #+#             */
/*   Updated: 2023/03/23 18:32:10 by wooseoki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

int	reduce_oper_command(t_stack **stack_node)
{
	t_stack	*next_node;

	next_node = (*stack_node)->next;
	(*stack_node)->next = next_node->next;
	pop_stack(&next_node);
	(*stack_node)->type = OPERATOR_CMD;
	return (SUCCESS);
}


