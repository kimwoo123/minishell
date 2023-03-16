/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recur_tree.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chajung <chajung@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 15:40:59 by chajung           #+#    #+#             */
/*   Updated: 2023/03/16 15:41:00 by chajung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_tree	*create_tree(int type, char *content, t_tree *left, t_tree *right)
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

t_tree	*create_root(void)
{
	t_tree	*root;
	t_tree	*group_cmd;
	t_tree	*parent_redir;
	t_tree	*command;

	root = create_tree(PIPE, NULL, NULL, NULL);
	if (root == NULL)
		return (NULL);
	group_cmd = create_tree(GROUP_CMD, NULL, NULL, NULL);
	if (root == NULL)
		return (NULL);
	root->left = group_cmd;
	parent_redir = create_tree(PARENT_REDIR, NULL, NULL, NULL);
	if (parent_redir == NULL)
		return (NULL);
	group_cmd->left = parent_redir;
	command = create_tree(COMMAND, NULL, NULL, NULL);
	if (parent_redir == NULL)
		return (NULL);
	group_cmd->right = command;
	return (root);
}

void	search_tree(t_tree *head)
{
	printf("type: %d\n", head->type);
	if (head->left != NULL)
		search_tree(head->left);
	if (head->right != NULL)
		search_tree(head->right);
}

void	add_root_node(t_tree **head)
{
	t_tree	*temp;

	temp = *head;
	while (temp != NULL)
		temp = temp->right;
	temp = create_root();
	if (temp == NULL)
		exit(EXIT_FAILURE);
}

void	recur_make_tree(t_tree **head, t_list *node)
{
	t_tree	*temp;

	if (node->type == PIPE)
		add_root_node(head);
	if (node->type == REDIRECTION)
		add_root_node(head);
	if (node->type == CMD_TOKEN)
		add_root_node(head);
	recur_make_tree(head, node->next);
}

int	test_tree(t_list **node)
{
	t_tree	*head;

	head = create_root();
	if (head == NULL)
		return (FAILURE);
	// search_tree(head);
	recur_make_tree(&head, *node);
	return (SUCCESS);
}
