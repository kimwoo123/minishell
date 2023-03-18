/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chajung <chajung@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 10:42:51 by chajung           #+#    #+#             */
/*   Updated: 2023/03/18 12:07:42 by wooseoki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// make_nodes_a_stack

static t_stack	*create_elem(int type)
{
	t_stack	*elem;

	elem = (t_stack *)malloc(sizeof(t_stack));
	if (elem == NULL)
		return (NULL);
	elem->type = type;
	elem->next = NULL;
	return (elem);
}

int	pop_stack(t_stack **stack)
{
	t_stack	*node;
	int		ret;

	if (*stack == NULL)
		return (0);
	ret = (*stack)->type;
	node = *stack;
	*stack = (*stack)->next;
	free(node);
	return (ret);
}

void	push_stack(t_stack **stack, int	type)
{
	t_stack *node;

	node = create_elem(type);
	if (node == NULL)
		return ;
	node->next = *stack;
	*stack = node;
}

t_tree	*create_tree(int type, char *content, t_tree *left, t_tree *right)
{
	t_tree	*tree;

	tree = (t_tree *)malloc(sizeof(t_tree));
	if (tree == NULL)
		return (NULL);
	tree->type = type;
	tree->content = content;
	tree->left = left;
	tree->right = right;
	return (tree);
}

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

static void	test_print_double_array(t_fptr **array)
{
	int	i;
	int	j;

	i = 0;
	while (i < 10)
	{
		j = 0;
		while (j < 10)
		{
			printf("i: %d, j: %d, array: %p\n", i, j, array[i][j]);
			j++;
		}
		i++;
	}
}

int	shift_command(t_stack **stack_node)
{
	t_stack *ct_node;

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

void	set_reduce_function(t_fptr **reduce_table)
{
	
	//reduce_table[COMMAND][CMD_TOKEN] = reduce_command;
	//reduce_table[COMMAND][REDIRECTION] = reduce_command;
	//reduce_table[REDIRECTION][PIPE] = shift_redir_command;
	//reduce_table[COMMAND][REDIR_TOKEN] = waiting;
	//reduce_table[PIPE_CMD][REDIR_TOKEN] = waiting;
	//reduce_table[COMMAND][0] = shift_l_command;
	//reduce_table[GROUP_CMD][0] = reduce_group_command;
	//reduce_table[COMMAND][WORD] = shift_word_command;
	//reduce_table[PIPE_CMD][WORD] = shift_word_command;
	//reduce_table[REDIRECTION][WORD] = shift_word_command;
	//reduce_table[GROUP_CMD][GROUP_CMD] = reduce_group_command;

	reduce_table[CMD_TOKEN][0] = shift_ct_command;
	reduce_table[WORD][0] = shift_w_ct;
	reduce_table[REDIRECTION][0] = shift_r_command;
	reduce_table[CMD_TOKEN][REDIR_TOKEN] = shift_command;
	reduce_table[CMD_TOKEN][PIPE] = shift_command;

	reduce_table[REDIR_TOKEN][WORD] = reduce_redirection;
	reduce_table[REDIRECTION][REDIRECTION] = reduce_redirection;
	reduce_table[WORD][WORD] = reduce_cmd_token;
	reduce_table[CMD_TOKEN][WORD] = reduce_cmd_token;
	reduce_table[COMMAND][COMMAND] = reduce_command;
	reduce_table[PIPE_CMD][COMMAND] = reduce_command;
	reduce_table[COMMAND][PIPE] = reduce_pipe_command;
	reduce_table[PIPE_CMD][PIPE_CMD] = reduce_pipe_command;
}

t_fptr **init_reduce_functions(void)
{
	t_fptr	**reduce_table;
	size_t	i;

	// PIPE enum is 9 so size is 10
	reduce_table = (t_fptr **)ft_calloc((PIPE + 1), sizeof(t_fptr *));
	if (!reduce_table)
		return (NULL);
	i = 0;
	while (i < PIPE + 1)
	{
		reduce_table[i] = (t_fptr *)ft_calloc((PIPE + 1), sizeof(t_fptr));
		++i;
	}
	set_reduce_function(reduce_table);
	return (reduce_table);
}

int	shift_token(t_fptr **reduce_table, t_stack **stack_node)
{
	int	s_type;

	if ((*stack_node) != NULL)
	{
		s_type = (*stack_node)->type;
		if (reduce_table[s_type][0])
		{
			reduce_table[s_type][0](stack_node);
			return (1);
		}
	}
	return (0);
}

int	reduce_token(t_fptr **reduce_table, t_stack **stack_node)
{
	int	s_type;
	int ns_type;

	if ((*stack_node) != NULL && (*stack_node)->next != NULL)
	{
		s_type = (*stack_node)->type;
		ns_type = (*stack_node)->next->type;
		if (reduce_table[ns_type][s_type])
		{
			reduce_table[ns_type][s_type](stack_node);
			return (1);
		}
	}
	return (0);
}

void	repeat_reduce_shift(t_fptr **reduce_table, t_stack **stack)
{
	t_stack *s_node;
	size_t	ret;

	while (1)
	{
		ret = 0;
		s_node = *stack;
		while (s_node)
		{
			ret += reduce_token(reduce_table, &s_node);
			if (ret)
				break ;
			ret += shift_token(reduce_table, &s_node);
			if (ret)
				break ;
			s_node = s_node->next;
		}
		if (ret == 0)
			break ;
	}
	if ((*stack && (*stack)->next == NULL) && ((*stack)->type == COMMAND || (*stack)->type == GROUP_CMD))
		printf("syntax fine\n");
	else
		printf("syntax error\n");
}

void	free_stack_table(t_stack *stack, t_fptr **table)
{
	t_stack *temp;
	t_stack *node;
	size_t	index;

	node = stack;
	while (node)
	{
		temp = node->next;
		free(node);
		node = temp;
	}
	index = 0;
	while (index < PIPE + 1)
	{
		free(table[index]);
		++index;
	}
	free(table);
	return ;
}

int	test_code(t_list **node)
{
	t_stack	*stack;
	t_list	*temp;
	t_fptr	**reduce_table;

	reduce_table = init_reduce_functions();
	stack = NULL;
	temp = *node;
	while (temp)
	{
		push_stack(&stack, temp->type);
		reduce_token(reduce_table, &stack);
		temp = temp->next;
	}
	repeat_reduce_shift(reduce_table, &stack);
	free_stack_table(stack, reduce_table);
	return (1);
}
