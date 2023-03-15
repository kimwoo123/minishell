/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chajung <chajung@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 10:42:51 by chajung           #+#    #+#             */
/*   Updated: 2023/03/15 19:09:33 by wooseoki         ###   ########.fr       */
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

int	ft_redirection(void)
{
	printf("REDIRECTIONS\n");
}

int	ft_command(void)
{
	printf("COMMAND\n");
}

int	ft_pipe_command(void)
{
	printf("PIPE_COMMAND\n");
}

int	kfc(void)
{
	printf("KFC\n");
	return (314);
}

typedef int (*funptr)(void);

funptr **init_reduce_functions(void)
{
	funptr	**reduce_table;
	int	i;

	reduce_table = (funptr **)malloc(sizeof(funptr *) * 10);
	i = 0;
	while (i < 10)
	{
		reduce_table[i] = (funptr *)malloc(sizeof(funptr) * 10);
		++i;
	}
	reduce_table[REDIR_TOKEN][WORD] = &ft_redirection;
	reduce_table[REDIRECTION][WORD] = &ft_redirection;
	reduce_table[WORD][WORD] = &ft_command;
	reduce_table[COMMAND][PIPE] = &ft_pipe_command;
	reduce_table[PIPE_CMD][PIPE_CMD] = &ft_pipe_command;
	reduce_table[COMMAND][COMMAND] = &ft_command;
	reduce_table[PIPE_CMD][COMMAND] = &ft_command;
	return (reduce_table);
}

void	print_reduce_functions(funptr **reduce_table, t_list *stack_node, t_list *list_node)
{
 	printf("%d, %d\n", stack_node->type, list_node->type);
 	printf("%p\n", &reduce_table[stack_node->type][list_node->type]);
  	reduce_table[stack_node->type][list_node->type]();
}

int	show_top_type(t_stack *stack_node, t_list *list_node)
{
	if (stack_node == NULL || list_node == NULL)
		return (-1);
	
	return (0);
}

int	test_code(t_list **node)
{
	t_stack *stack;
	t_list	*temp;
	t_tree	*root;

	funptr **reduce_table;

	reduce_table = init_reduce_functions();
	print_reduce_functions(reduce_table, *node, (*node)->next);

	// stack = NULL;
	// root = create_tree(0, NULL, NULL, NULL);
	// if (root == NULL)
	// 	return (0);
	// temp = *node;
	// print_reduce_functions(reduce_table, temp, temp->next);
	// while (temp)
	// {
	// 	// push_stack(&stack, (temp)->type, (temp)->content); // check
	// 	// show_top_type(stack, temp);
	// 	print_reduce_functions(reduce_table, temp, temp->next);
	// 	temp = temp->next;
	// }
	// print_list(&stack);
	return (0);
}

