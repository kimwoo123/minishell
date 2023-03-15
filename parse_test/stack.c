/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chajung <chajung@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 10:42:51 by chajung           #+#    #+#             */
/*   Updated: 2023/03/15 15:41:21 by wooseoki         ###   ########.fr       */
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

char	*pop_stack(t_stack **stack)
{
	t_stack	*node;
	int		ret;

	if (*stack == NULL)
		return (NULL);
	ret = (*stack)->content;
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

int	test_code(t_list **node)
{
	t_stack *stack;
	t_list	*temp;

	stack = NULL;
	int		i;
	i = 0;
	temp = *node;
	while (temp)
	{
		push_stack(&stack, (temp)->type, (temp)->content);
		temp = temp->next;	
		i++;
	}
	print_list(&stack);
}
