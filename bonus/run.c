/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chajung <chajung@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 10:54:03 by chajung           #+#    #+#             */
/*   Updated: 2023/03/22 10:54:04 by chajung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

static int	init_backup(t_data *data)
{
	data->count_cmd = 0;
	data->pid = 0;
	data->last_cmd = FALSE;
	data->has_forked = FALSE;
	data->dup_stdin = dup(STDIN_FILENO);
	if (data->dup_stdin == FAILURE)
		return (FAILURE);
	data->dup_stdout = dup(STDOUT_FILENO);
	if (data->dup_stdout == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}

static int	restore(t_data *data)
{
	if (dup2(data->dup_stdin, STDIN_FILENO) == FAILURE)
		return (FAILURE);
	if (dup2(data->dup_stdout, STDOUT_FILENO) == FAILURE)
		return (FAILURE);
	if (close(data->dup_stdin) == FAILURE)
		return (FAILURE);
	if (close(data->dup_stdout) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}

void	waiting(t_data *data)
{
	extern int	g_status;
	int			count;

	if (data->count_cmd == 0 || data->pid == -1)
		return ;
	if (data->count_cmd > 0)
		if (waitpid(data->pid, &g_status, 0) == FAILURE)
			exit_with_str("A wait error in waiting", EXIT_FAILURE);
	count = 1;
	while (count < data->count_cmd)
	{
		if (wait(NULL) == FAILURE)
			exit_with_str("B wait error in waiting", EXIT_FAILURE);
		count++;
	}
}

void	recursive_make_tree_tester(t_tree **head, t_list *node, t_list **temp)
{
	// dprintf(2, "---------------------\n");
	// dprintf(2, "type: %d\n", node->type);
	// dprintf(2, "cont: %s\n", node->content);
	// dprintf(2, "---------------------\n");
	if (node == NULL)
	{
		*temp = node;
		return ;
	}
	if (node->type == OPERATOR)
	{
		*temp = node;
		return ;
	}
	if (node->type == PIPE)
	{
		add_pipe(head);
		recursive_make_tree_tester(head, node->next, temp);
	}
	else if (node->type == REDIR_TOKEN)
	{
		add_redirections(head, node, node->next);
		recursive_make_tree_tester(head, node->next->next, temp);
	}
	else if (node->type == WORD)
	{
		add_commands(head, node);
		recursive_make_tree_tester(head, node->next, temp);
	}
}

t_tree	*make_tree_before_operator(t_list **addr)
{
	t_tree	*head;
	t_list	*temp;

	head = create_root();
	if (head == NULL)
		exit_with_str("malloc error in make tree", EXIT_FAILURE);
	recursive_make_tree_tester(&head, *addr, &temp);
	*addr = temp;
	// temp = node;
	// dprintf(2, "---------------------\n");
	// dprintf(2, "type: %d\n", temp->type);
	// dprintf(2, "cont: %s\n", temp->content);
	// dprintf(2, "next: %p\n", temp->next);
	// dprintf(2, "---------------------\n");
	// dprintf(2, "---------------------\n");
	// dprintf(2, "type: %d\n", temp->next->type);
	// dprintf(2, "cont: %s\n", temp->next->content);
	// dprintf(2, "next: %p\n", temp->next->next);
	// dprintf(2, "---------------------\n");
	return (head);
}

void	make_tree_tester(t_data *data, t_list **addr)
{
	t_tree *tree;
	int		flag;

	if (init_backup(data) == FAILURE)
		exit_with_str("backup error in run minishell", EXIT_FAILURE);
	if ((*addr)->type == OPERATOR)
	{
		flag = TRUE;

		// if (is_equal_to((*addr)->content, AND)


		(*addr) = (*addr)->next;
		tree = make_tree_before_operator(addr);
		// if (flag == TRUE)
		search_tree_for_hd(data, tree);
		search_tree(data, tree);
		waiting(data);
	}
	else
	{

		tree = make_tree_before_operator(addr);
		search_tree_for_hd(data, tree);
		search_tree(data, tree);
		waiting(data);
	}
	free_tree(tree);
	if (restore(data) == FAILURE)
		exit_with_str("restore error in run minishell", EXIT_FAILURE);
}

void	run_minishell(t_data *data, char *command_line)
{
	t_list	*list;
	t_list	*addr;

	list = scan_command(command_line, data);
	if (list == NULL)
		rl_on_new_line();
	else
	{
		addr = list;
		while (addr != NULL)
			make_tree_tester(data, &addr);
		free_list(&list);
	}
}

// void	run_minishell(t_data *data, char *command_line)
// {
// 	t_list	*list;
// 	t_tree	*tree;

// 	data->count_cmd = 0;
// 	data->pid = 0;
// 	data->last_cmd = FALSE;
// 	data->has_forked = FALSE;
// 	if (backup_stdio(data) == FAILURE)
// 		exit_with_str("backup error in run minishell", EXIT_FAILURE);
// 	list = scan_command(command_line, data);
// 	if (list == NULL)
// 		rl_on_new_line();
// 	else
// 	{	
// 		tree = make_tree(&list);
// 		search_tree_for_hd(data, tree);
// 		search_tree(data, tree);
// 		waiting(data);
// 		free_list(&list);
// 		free_tree(tree);
// 	}
// 	if (restore_stdio(data) == FAILURE)
// 		exit_with_str("restore error in run minishell", EXIT_FAILURE);
// }
