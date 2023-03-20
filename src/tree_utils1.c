/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_utils1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chajung <chajung@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 15:46:59 by chajung           #+#    #+#             */
/*   Updated: 2023/03/20 15:47:00 by chajung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

static t_tree	*add_redirection(t_tree **head, t_list *node, t_list *next_node)
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
	while (temp->right != NULL)
		temp = temp->right;
	while (temp->type != PARENT_REDIR)
		temp = temp->left;
	while (temp->right != NULL)
		temp = temp->right;
	temp->left = add_redirection(head, node, next_node);
	if (temp->left == NULL)
		perror("error in add redirections");
	temp->right = create_tree(PARENT_REDIR, NULL, NULL, NULL);
	if (temp->right == NULL)
		perror("error in add redirections");
}

static t_tree	*add_command(t_tree **head, t_list *node)
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
	while (temp->right != NULL)
		temp = temp->right;
	temp = temp->left->right;
	while (temp->right != NULL)
		temp = temp->right;
	temp->left = add_command(head, node);
	if (temp->left == NULL)
		perror("error in add commands");
	temp->right = create_tree(COMMAND, NULL, NULL, NULL);
	if (temp->right == NULL)
		perror("error in add commands");
}
