/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_utils0.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chajung <chajung@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 16:15:54 by chajung           #+#    #+#             */
/*   Updated: 2023/03/20 16:15:55 by chajung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

t_tree	*create_tree(int type, char *content, t_tree *left, t_tree *right)
{
	t_tree	*tree;

	tree = (t_tree *)malloc(sizeof(t_tree));
	if (tree == NULL)
		return (NULL);
	tree->type = type;
	if (content)
	{
		tree->content = ft_strdup(content);
		if (tree->content == NULL)
			return (NULL);
	}
	else
		tree->content = NULL;
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

	root = create_tree(PIPE, "|", NULL, NULL);
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
	command = create_tree(PARENT_CMD, NULL, NULL, NULL);
	if (parent_redir == NULL)
		return (NULL);
	group_cmd->right = command;
	return (root);
}

static void	recursive_make_tree(t_data *data, \
	t_tree **head, t_list *node, t_list **temp)
{
	if (node == NULL || node->type == OPERATOR)
	{
		*temp = node;
		return ;
	}
	if (node->type == SUBS_OPEN || node->type == SUBSHELL)
	{
		data->sub_flag = TRUE;
		recursive_make_tree(data, head, node->next, temp);
	}
	if (node->type == PIPE)
	{
		add_pipe(head);
		recursive_make_tree(data, head, node->next, temp);
	}
	else if (node->type == REDIR_TOKEN)
	{
		add_redirections(head, node, node->next);
		recursive_make_tree(data, head, node->next->next, temp);
	}
	else if (node->type == WORD)
	{
		add_commands(head, node);
		recursive_make_tree(data, head, node->next, temp);
	}
}

t_tree	*make_tree(t_data *data, t_list **node)
{
	t_tree	*head;
	t_list	*temp;

	head = create_root();
	if (head == NULL)
		exit_with_str("malloc error in make tree", EXIT_FAILURE);
	temp = NULL;
	recursive_make_tree(data, &head, *node, &temp);
	*node = temp;
	return (head);
}
