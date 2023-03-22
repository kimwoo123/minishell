#include "minishell.h"

static int	backup_stdio(t_data *data)
{
	data->dup_stdin = ft_dup(STDIN_FILENO);
	if (data->dup_stdin == FAILURE)
		return (FAILURE);
	data->dup_stdout = ft_dup(STDOUT_FILENO);
	if (data->dup_stdout== FAILURE)
		return (FAILURE);
	return (SUCCESS);
}

static int	restore_stdio(t_data *data)
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

void	run_minishell(t_data *data, char *command_line)
{
	t_list	*list;
	t_tree	*tree;

	data->last_cmd = FALSE;
	data->has_forked = FALSE;
	if (backup_stdio(data) == FAILURE)
		exit_with_str("backup error in run minishell", EXIT_FAILURE);
	list = scan_command(command_line, data);
	if (list == NULL)
		rl_on_new_line();
	else
	{
		tree = make_tree(&list);
		search_tree_for_hd(data, tree);
		search_tree(data, tree);
		free_list(&list);
		free_tree(tree);
	}
	if (restore_stdio(data) == FAILURE)
		exit_with_str("backup error in run minishell", EXIT_FAILURE);
}
