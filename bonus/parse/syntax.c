/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chajung <chajung@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 10:42:51 by chajung           #+#    #+#             */
/*   Updated: 2023/03/26 12:07:18 by wooseoki         ###   ########.fr       */
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

int	reduce_shift(t_fptr **parse_table, t_stack **stack)
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

char	*map[] = {
	"ZERO",
	"WORD",
	"REDIR_TOKEN",
	"REDIRECTION",
	"CMD_TOKEN",
	"COMMAND",
	"PIPE_CMD",
	"OPERATOR",
	"OPERATOR_CMD",
	"SUBSHELL",
	"GROUP_CMD",
	"SUBS_CMD",
	"PIPE"
};

void p_s(t_stack *stack)
{
	printf("==============\n");
	while (stack)
	{
		printf("%s\n", map[stack->type]);
		stack = stack->next;
	}	
}

int	repeat_reduce_shift(t_fptr **parse_table, t_stack **stack)
{
	size_t	ret;

	ret = 1;
	while (ret != 0)
	{
		ret = reduce_shift(parse_table, stack);
		if (ret == 0)
			break ;
	}

	if ((*stack && (*stack)->next == NULL) && \
		((*stack)->type == COMMAND || ((*stack)->type == GROUP_CMD) || (*stack)->type == SUBSHELL))
		return (TRUE);
	return (FALSE);
}

int	check_syntax(t_list **token_list)
{
	int			accept;

	if (*token_list == NULL)
		return (TRUE);
	accept = parse_token(token_list);
	if (accept == FALSE)
	{
		ft_putendl_fd("syntax error", STDERR_FILENO);
		return (FALSE);
	}
	return (TRUE);
}
