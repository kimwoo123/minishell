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
	command = create_tree(COMMAND, NULL, NULL, NULL);
	if (parent_redir == NULL)
		return (NULL);
	group_cmd->right = command;
	return (root);
}

void	add_pipe(t_tree **head)
{
	t_tree	*temp;

	temp = *head;
	while (temp->right != NULL)
		temp = temp->right;
	temp->right = create_root();
	if (temp->right == NULL)
		perror("error in add root node");
}

t_tree	*add_redirection(t_tree **head, t_list *node, t_list *next_node)
{
	t_tree	*redir;
	t_tree	*temp;

	redir = create_tree(REDIRECTION, NULL, NULL, NULL);
	if (redir == NULL)
		perror("error in add redirection");
	redir->left = create_tree(REDIR_TOKEN, node->content, NULL, NULL);
	if (redir->left == NULL)
		perror("error in add redirection");
	redir->right = create_tree(WORD, next_node->content, NULL, NULL);
	if (redir->right == NULL)
		perror("error in add redirection");
	return (redir);
}

void	add_redirections(t_tree **head, t_list *node, t_list *next_node)
{
	t_tree	*temp;

	temp = *head;
	while (temp->right != NULL) // PIPE CHECK
		temp = temp->right;
	while (temp->type != PARENT_REDIR) // SEARCH PARENT REDIRECTION
		temp = temp->left;
	while (temp->right != NULL) // CHECHK THERE IS PR ON RIGHT
		temp = temp->right; // TEMP->RIGHT = NULL
	temp->left = add_redirection(head, node, next_node);
	if (temp->left == NULL)
		perror("error in add redirections");
	temp->right = create_tree(PARENT_REDIR, NULL, NULL, NULL);
	if (temp->right == NULL)
		perror("error in add redirections");
}

t_tree	*add_command(t_tree **head, t_list *node)
{
	t_tree	*command;
	t_tree	*temp;

	command = create_tree(CMD_TOKEN, node->content, NULL, NULL);
	if (command == NULL)
		perror("error in add command");
	return (command);
}

void	add_commands(t_tree **head, t_list *node)
{
	t_tree	*temp;

	temp = *head;
	while (temp->right != NULL) // PIPE CHECK
		temp = temp->right;
	temp = temp->left->right; // PIPE -> GROUP_COMMAND -> COMMAND
	while (temp->right != NULL) // CHECHK THERE IS COMMAND ON RIGHT
		temp = temp->right; // TEMP->RIGHT = NULL, NOW WE ARE AT COMMAND
	temp->left = add_command(head, node);
	if (temp->left == NULL)
		perror("error in add commands");
	temp->right = create_tree(COMMAND, NULL, NULL, NULL); // CREATE COMMAND
	if (temp->right == NULL)
		perror("error in add commands");
}

void	recursive_make_tree(t_tree **head, t_list *node)
{
	t_tree	*temp;

	if (node == NULL)
		return ;
	else if (node->type == PIPE)
	{
		add_pipe(head);
		recursive_make_tree(head, node->next);
	}
	else if (node->type == REDIR_TOKEN)
	{
		add_redirections(head, node, node->next);
		recursive_make_tree(head, node->next->next);
	}
	else if (node->type == WORD)
	{
		add_commands(head, node);
		recursive_make_tree(head, node->next);
	}
}

static void	test_search_tree(t_tree *head)
{
	if (head && head->content)
		printf("type: %d, content:%s\n", head->type, head->content);
	if (head->left != NULL)
		test_search_tree(head->left);
	if (head->right != NULL)
		test_search_tree(head->right);
}

t_tree	*make_tree(t_list **node)
{
	t_tree	*head;

	head = create_root();
	if (head == NULL)
		return (NULL);
	recursive_make_tree(&head, *node);
	// test_search_tree(head);
	return (head);
}
