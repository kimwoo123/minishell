/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chajung <chajung@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 10:42:51 by chajung           #+#    #+#             */
/*   Updated: 2023/03/18 10:53:35 by wooseoki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// make_nodes_a_stack
char *trans[] = { "ZERO", "WORD", "REDIR_TOKEN", "REDIRECTION",
				"CMD_TOKEN", "COMMAND", "PIPE_CMD", "PARENT_REDIR", "GROUP_CMD", "QUOTE", "PIPE" };


static void	print_list(t_stack **node)
{
	t_stack	*temp;

	temp = *node;
	while (temp)
	{
		printf("type: %d\n", temp->type);
		temp = temp->next;
	}
}

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

int	waiting(t_stack **stack_node)
{
	return (SUCCESS);
}

typedef int (*t_fptr)(t_stack **stack_node);

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

int	shift_word_command(t_stack **stack_node)
{
	// if (list_node->type != WORD)
	// 	return (FAILURE);
	pop_stack(stack_node);
	push_stack(stack_node, CMD_TOKEN);
	return (SUCCESS);
}

int	shift_word2_command(t_stack **stack_node)
{	
	t_stack *next_node;

	next_node = (*stack_node)->next;
	next_node->type = CMD_TOKEN;

	return (SUCCESS);
}

int	shift_command(t_stack **stack_node)
{
	t_stack *ct_node;

	ct_node = (*stack_node)->next;
	ct_node->type = COMMAND;

	return (SUCCESS);
}

int	shift_redir_command(t_stack **stack_node)
{
	int	type;

	type = pop_stack(stack_node);
	pop_stack(stack_node);
	push_stack(stack_node, REDIRECTION);
	push_stack(stack_node, type);
	return (SUCCESS);
}

int	shift_gc_command(t_stack **stack_node)
{	
	t_stack *cmd_node;

	cmd_node = (*stack_node)->next;
	cmd_node->type = GROUP_CMD;

	return (SUCCESS);
}

int	shift_l_command(t_stack **stack_node)
{
	int	out_type;
	int	in_type;

	out_type = (*stack_node)->type;
	if (out_type == CMD_TOKEN)
		in_type = COMMAND;
	else if (out_type == WORD)
		in_type = CMD_TOKEN;
	else if (out_type == REDIRECTION)
		in_type = COMMAND;
	(*stack_node)->type = in_type;
	return (SUCCESS);
}

void	init_reduce_functions2(t_fptr **reduce_table)
{
	reduce_table[CMD_TOKEN][0] = shift_l_command;
	reduce_table[WORD][0] = shift_l_command;
	reduce_table[REDIRECTION][0] = shift_l_command;
	//reduce_table[COMMAND][0] = shift_l_command;
	//reduce_table[GROUP_CMD][0] = reduce_group_command;
	
	reduce_table[COMMAND][WORD] = shift_word_command;
	reduce_table[PIPE_CMD][WORD] = shift_word_command;
	reduce_table[REDIRECTION][WORD] = shift_word_command;

	reduce_table[CMD_TOKEN][REDIR_TOKEN] = shift_command;
	reduce_table[CMD_TOKEN][PIPE] = shift_command;

	//reduce_table[REDIRECTION][PIPE] = shift_redir_command;

	//reduce_table[COMMAND][REDIR_TOKEN] = waiting;
	//reduce_table[PIPE_CMD][REDIR_TOKEN] = waiting;
	reduce_table[REDIR_TOKEN][WORD] = reduce_redirection;
	reduce_table[REDIRECTION][REDIRECTION] = reduce_redirection;
	reduce_table[WORD][WORD] = reduce_cmd_token;
	reduce_table[CMD_TOKEN][WORD] = reduce_cmd_token;
	reduce_table[COMMAND][CMD_TOKEN] = reduce_command;
	reduce_table[COMMAND][PIPE] = reduce_pipe_command;
	reduce_table[PIPE_CMD][PIPE_CMD] = reduce_pipe_command;
	reduce_table[PIPE_CMD][COMMAND] = reduce_group_command;
	reduce_table[GROUP_CMD][GROUP_CMD] = reduce_group_command;
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
	init_reduce_functions2(reduce_table);
	return (reduce_table);
}

/*
void	print_reduce_functions(t_fptr **reduce_table, t_list *stack_node)
{
 	printf("%d, %d\n", stack_node->type, list_node->type);
 	printf("%p\n", &reduce_table[stack_node->type][list_node->type]);
  	if (reduce_table[stack_node->type][list_node->type] == NULL)
	  	return ;
}
*/

int	test_shift(t_fptr **reduce_table, t_stack **stack_node)
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

int	test_reduce(t_fptr **reduce_table, t_stack **stack_node)
{
	int	s_type;
	int ns_type;

	if ((*stack_node) != NULL && (*stack_node)->next != NULL)
	{
		s_type = (*stack_node)->type;
		ns_type = (*stack_node)->next->type;
		printf("before: %s, %s\n", trans[ns_type], trans[s_type]);
		if (reduce_table[ns_type][s_type])
		{
			// printf("after: %s, %s\n", trans[s_type], trans[ns_type]);
			reduce_table[ns_type][s_type](stack_node);
			return (1);
		}
	}
	return (0);
}

void	repeat_reduce(t_fptr **reduce_table, t_stack **s_node)
{
	
}
int	test_code(t_list **node)
{
	t_stack *stack;
	t_list	*temp;
	t_tree	*root;
	t_fptr **reduce_table;
	t_stack *s_node;

	reduce_table = init_reduce_functions();
	stack = NULL;
	root = create_tree(0, NULL, NULL, NULL);
	if (root == NULL)
		return (0);
	temp = *node;
	while (temp)
	{
		push_stack(&stack, temp->type);
		test_reduce(reduce_table, &stack);
		temp = temp->next;
	}
	repeat_reduce(reduce_table, &stack);
	int	flag;
	int ret;

	while (1)
	{
		ret = 0;
		s_node = stack;
		while (s_node)
		{
			ret += test_reduce(reduce_table, &s_node);
			if (ret)
				break ;
			ret += test_shift(reduce_table, &s_node);
			if (ret)
				break ;
			s_node = s_node->next;
		}
		if (ret == 0)
			break ;
	}
	/*
	while (stack)
	{
		printf("stack %d: %s\n", stack->type, trans[stack->type]);
		stack = stack->next;
	}
	*/
	if ((stack && stack->next == NULL) && (stack->type == COMMAND || stack->type == GROUP_CMD))
		printf("syntax fine\n");
	else
		printf("sytanx error\n");
	return (0);
}
