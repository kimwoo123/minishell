/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chajung <chajung@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 10:42:51 by chajung           #+#    #+#             */
/*   Updated: 2023/03/16 15:11:04 by wooseoki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// make_nodes_a_stack

static void	print_list(t_stack **node)
{
	t_stack	*temp;

	temp = *node;
	while (temp)
	{
		printf("type: %d, content: %s\n", temp->type, temp->content);
		temp = temp->next;
	}
}

static t_stack	*create_elem(int type, char *content)
{
	t_stack	*elem;

	elem = (t_stack *)malloc(sizeof(t_stack));
	if (elem == NULL)
		return (NULL);
	elem->type = type;
	elem->content = content;
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

void	push_stack(t_stack **stack, int	type, char *content)
{
	t_stack *node;

	node = create_elem(type, content);
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

/*
S' -> S
S -> SP S
S -> S S
SP -> SP SP
SP -> S P
S -> C
S -> R
C -> C W
C -> W
R -> R R
R -> r W

reduce_rule_0 // r W
reduce_rule_1 // R R
reduce_rule_2 // W
reduce_rule_3 // C W
reduce_rule_4 // R
reduce_rule_5 // C
reduce_rule_6 // S P
reduce_rule_7 // SP SP
reduce_rule_8 // S S
reduce_rule_9 // SP S
reduce_rule_10 // S'
*/

// void	shift_functions(t_stack *stack_node, t_list *list_node)
// {
// 	shift_function[WORD] = CMD_TOKEN;
// 	shift_function[REDIRECTION] = COMMAND;
// 	shift_function[CMD_TOKEN] = COMMAND;
// 	shift_function[COMMAND] = GROUP_CMD;
// }


int	reduce_redirection(t_stack **stack_node, t_list *list_node) // r W / R R
{
	t_stack *node;

	pop_stack(stack_node);
	push_stack(stack_node, REDIRECTION, NULL);


	return (SUCCESS);
}

int	reduce_cmd_token(t_stack **stack_node, t_list *list_node) // C W
{
	t_stack *node;

	pop_stack(stack_node);
	push_stack(stack_node, CMD_TOKEN, NULL);

	return (SUCCESS);
}

int	reduce_pipe_command(t_stack **stack_node, t_list *list_node) // SP SP
{
	t_stack *node;

	pop_stack(stack_node);
	push_stack(stack_node, PIPE_CMD, NULL);

	return (SUCCESS);
}

int	reduce_group_command(t_stack **stack_node, t_list *list_node) // S S / SP P
{
	t_stack *node;

	pop_stack(stack_node);
	push_stack(stack_node, GROUP_CMD, NULL);

	return (SUCCESS);
}

int	waiting(t_stack **stack_node, t_list *list_node)
{
	return (SUCCESS);
}

typedef int (*t_fptr)(t_stack **stack_node, t_list *list_node);

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

int	shift_word_command(t_stack **stack_node, t_list *list_node)
{
	// if (list_node->type != WORD)
	// 	return (FAILURE);
	pop_stack(stack_node);
	push_stack(stack_node, CMD_TOKEN, NULL);
	return (SUCCESS);
}

int	shift_command(t_stack **stack_node, t_list *list_node)
{
	int	type;

	type = pop_stack(stack_node);
	pop_stack(stack_node);
	push_stack(stack_node, COMMAND, NULL);
	push_stack(stack_node, type, NULL);
	return (SUCCESS);
}

int	shift_redir_command(t_stack **stack_node, t_list *list_node)
{
	int	type;

	type = pop_stack(stack_node);
	pop_stack(stack_node);
	push_stack(stack_node, REDIRECTION, NULL);
	push_stack(stack_node, type, NULL);
	return (SUCCESS);
}

int	shift_gc_command(t_stack **stack_node, t_list *list_node)
{
	int	type;

	type = pop_stack(stack_node);
	pop_stack(stack_node);
	push_stack(stack_node, GROUP_CMD, NULL);
	push_stack(stack_node, type, NULL);
	return (SUCCESS);
}

void	init_reduce_functions2(t_fptr **reduce_table)
{
	// reduce_table[WORD][WORD] = ;
	// reduce_table[WORD][REDIR_TOKEN] = reduce_cmd_token;
	// reduce_table[WORD][PIPE] = reduce_cmd_token;
	// reduce_table[WORD][0] = reduce_cmd_token;

	reduce_table[COMMAND][WORD] = shift_word_command;
	reduce_table[PIPE_CMD][WORD] = shift_word_command;
	reduce_table[REDIRECTION][WORD] = shift_word_command;

	reduce_table[CMD_TOKEN][REDIR_TOKEN] = shift_command;
	reduce_table[CMD_TOKEN][PIPE] = shift_command;
	reduce_table[CMD_TOKEN][0] = shift_command;

	reduce_table[REDIRECTION][PIPE] = shift_redir_command;
	reduce_table[REDIRECTION][0] = shift_redir_command;

	reduce_table[COMMAND][0] = shift_gc_command;

	reduce_table[REDIR_TOKEN][WORD] = reduce_redirection;
	reduce_table[CMD_TOKEN][WORD] = reduce_cmd_token;
	reduce_table[COMMAND][PIPE] = reduce_pipe_command;
	reduce_table[PIPE_CMD][PIPE_CMD] = reduce_pipe_command;
	reduce_table[REDIRECTION][REDIRECTION] = reduce_redirection;
	reduce_table[PIPE_CMD][COMMAND] = reduce_group_command;
	reduce_table[GROUP_CMD][GROUP_CMD] = reduce_group_command;
	reduce_table[GROUP_CMD][0] = reduce_group_command;

	reduce_table[COMMAND][REDIR_TOKEN] = waiting;
	reduce_table[PIPE_CMD][REDIR_TOKEN] = waiting;
	reduce_table[REDIRECTION][REDIR_TOKEN] = waiting;

	// reduce_table[REDIR_TOKEN][REDIR_TOKEN] = ERROR;
	// reduce_table[REDIR_TOKEN][PIPE] = ERROR;
	// reduce_table[REDIR_TOKEN][0] = ERROR;
	// reduce_table[PIPE_CMD][PIPE] = ERROR;
	// reduce_table[PIPE_CMD][0] = ERROR;
}

t_fptr **init_reduce_functions(void)
{
	t_fptr	**reduce_table;
	size_t	i;

	// PIPE enum is 9 so size is 10
	reduce_table = (t_fptr **)ft_calloc((PIPE + 1), sizeof(t_fptr *));
	if (!reduce_table)
		return (NULL);
	i = -1;
	while (++i < PIPE + 1)
		reduce_table[i] = (t_fptr *)ft_calloc((PIPE + 1), sizeof(t_fptr));

	// test_print_double_array(reduce_table);

	reduce_table[REDIR_TOKEN][WORD] = reduce_redirection;
	reduce_table[REDIRECTION][REDIRECTION] = reduce_redirection;
	reduce_table[CMD_TOKEN][WORD] = reduce_cmd_token;
	reduce_table[PIPE_CMD][PIPE_CMD] = reduce_pipe_command;
	reduce_table[GROUP_CMD][GROUP_CMD] = reduce_group_command;
	reduce_table[PIPE_CMD][GROUP_CMD] = reduce_group_command;
	init_reduce_functions2(reduce_table);
	return (reduce_table);
}

void	print_reduce_functions(t_fptr **reduce_table, t_list *stack_node, t_list *list_node)
{
 	printf("%d, %d\n", stack_node->type, list_node->type);
 	printf("%p\n", &reduce_table[stack_node->type][list_node->type]);
  	if (reduce_table[stack_node->type][list_node->type] == NULL)
	  	return ;
}

int	show_top_type(t_stack *stack_node, t_list *list_node)
{
	if (stack_node == NULL || list_node == NULL)
		return (-1);
	return (0);
}

void	test_shift(t_stack **stack_node, t_list *list_node)
{
	// W -> C
	if (*stack_node == NULL)
		return ;
	if (list_node == NULL)
	{
		if ((*stack_node)->type == WORD)
			(*stack_node)->type = CMD_TOKEN;
		if ((*stack_node)->type == CMD_TOKEN)
			(*stack_node)->type = COMMAND;
		if ((*stack_node)->type == REDIRECTION)
			(*stack_node)->type = COMMAND;
		if ((*stack_node)->type == COMMAND)
			(*stack_node)->type = GROUP_CMD;
		if ((*stack_node)->type == COMMAND)
			(*stack_node)->type = GROUP_CMD;
		return ;
	}
	if ((*stack_node)->type == WORD)
		(*stack_node)->type = CMD_TOKEN;
	if ((*stack_node)->type == CMD_TOKEN && list_node->type != WORD)
		(*stack_node)->type = COMMAND;
	if ((*stack_node)->type == REDIRECTION && list_node->type != REDIR_TOKEN)
		(*stack_node)->type = COMMAND;
}

void	test_reduce(t_fptr **reduce_table, t_stack **stack_node, t_list *list_node)
{
	if (list_node == NULL)
		return ;
	if (*stack_node == NULL \
	|| reduce_table[(*stack_node)->type][list_node->type] == NULL)
	{
		push_stack(stack_node, list_node->type, list_node->content);
		return ;
	}
	reduce_table[(*stack_node)->type][list_node->type](stack_node, list_node);
	// printf("%d\n", (*stack_node)->type);
}

int	test_code(t_list **node)
{
	t_stack *stack;
	t_list	*temp;
	t_tree	*root;
	t_fptr **reduce_table;

	reduce_table = init_reduce_functions();
	// print_reduce_functions(reduce_table, *node, (*node)->next);

	stack = NULL;
	root = create_tree(0, NULL, NULL, NULL);
	if (root == NULL)
		return (0);
	temp = *node;
	// print_reduce_functions(reduce_table, temp, temp->next);
	int	i;

	i = 0;
	while (i++ < 100)
	{
		test_shift(&stack, temp);
		test_reduce(reduce_table, &stack, temp);
		// i = 0;
		// while (i++ < 5)
		// 	test_shift(&stack, temp);
		// push_stack(&stack, (temp)->type, (temp)->content); // check
		// show_top_type(stack, temp);
		// print_reduce_functions(reduce_table, temp, temp->next);
		if (temp)
			temp = temp->next;
		if (stack->type == GROUP_CMD)
			break ;
		// printf("TEST\n");
	}
	printf("%d\n", i);
	print_list(&stack);
	return (0);
}
