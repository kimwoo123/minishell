/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chajung <chajung@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 10:42:51 by chajung           #+#    #+#             */
/*   Updated: 2023/03/25 17:40:41 by wooseoki         ###   ########.fr       */
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

char *map[] = {"ZERO", "WORD", "R_T", "RE", "C_T", "CMD", "P_CMD", "P_R", "P_C", "OPER", "OP_CMD", "S_O", "S_C", "S_CMD", "SUB", "PIPE"};

int	repeat_reduce_shift(t_fptr **parse_table, t_stack **stack)
{
	t_stack	*s_node;
	size_t	ret;

//	int d;

	while (1)
	{
		ret = 0;
		s_node = *stack;
		while (s_node)
		{		
			/*
			d = s_node->type;
			printf("r----------\n");
			printf("%s\n", map[d]);
			if (s_node->next)
			{
				d = s_node->next->type;
				printf("%s\n", map[d]);
			}
			printf("-----------\n");
			*/
			ret += reduce_token(parse_table, &s_node);
			if (ret)
				break ;
			s_node = s_node->next;
		}
		if (ret == 0)
		{
			
			s_node = *stack;
			while (s_node)
			{
				/*
				d = s_node->type;
				printf("s----------\n");
				printf("%s\n", map[d]);
				if (s_node->next)
				{
					d = s_node->next->type;
					printf("%s\n", map[d]);
				}
				printf("-----------\n");
				*/
				ret += shift_token(parse_table, &s_node);
				if (ret)
					break ;
				s_node = s_node->next;
			}
		}
		if (ret == 0)
			break ;
		printf("no");
	}
	if ((*stack && (*stack)->next == NULL) && \
		((*stack)->type == COMMAND || (*stack)->type == SUBSHELL))
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
		ft_putendl_fd("syntax error", STDERR_FILENO);
		return (FALSE);
	}
	return (TRUE);
}
