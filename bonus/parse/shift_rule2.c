/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shift_rule2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wooseoki <wooseoki@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 14:01:55 by wooseoki          #+#    #+#             */
/*   Updated: 2023/03/27 14:08:07 by wooseoki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

int	shift_group_cmd(t_stack **stack_node)
{
	(*stack_node)->type = GROUP_CMD;
	return (SUCCESS);
}
