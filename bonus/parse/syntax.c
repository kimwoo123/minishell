/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chajung <chajung@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 10:42:51 by chajung           #+#    #+#             */
/*   Updated: 2023/03/26 15:54:24 by wooseoki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

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

int	reduce_shift(t_fptr **parse_table, t_stack **stack, int flag)
{
	t_stack	*s_node;
	size_t	ret;

	ret = 0;
	s_node = *stack;
	while (s_node)
	{		
		ret += reduce_token(parse_table, &s_node);
		s_node = s_node->next;
	}
	if (ret)
		return (1);
	if (flag == 0)
		return (0);
	s_node = *stack;
	while (s_node)
	{				
		ret += shift_token(parse_table, &s_node);
		s_node = s_node->next;
	}
	if (ret)
		return (1);
	return (0);
}

int	repeat_reduce_shift(t_fptr **parse_table, t_stack **stack, int flag)
{
	size_t	ret;

	ret = 1;
	while (ret != 0)
	{
		ret = reduce_shift(parse_table, stack, flag);
		if (ret == 0)
			break ;
	}
	if ((*stack && (*stack)->next == NULL) && \
		((*stack)->type == COMMAND || ((*stack)->type == GROUP_CMD)))
		return (TRUE);
	return (FALSE);
}

int	check_syntax(t_list **token_list)
{
	extern int	g_status;
	int			accept;

	if (*token_list == NULL)
		return (TRUE);
	accept = parse_token(token_list);
	if (accept == FALSE)
	{
		ft_putendl_fd("syntax error", STDERR_FILENO);
		g_status = -1;
		return (FALSE);
	}
	return (TRUE);
}
