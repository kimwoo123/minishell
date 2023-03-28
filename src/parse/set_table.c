/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_table.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wooseoki <wooseoki@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 15:27:38 by wooseoki          #+#    #+#             */
/*   Updated: 2023/03/27 13:10:56 by wooseoki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

void	set_subshell_function(t_fptr **parse_table)
{
	parse_table[SUBSHELL][0] = &shift_s_cmd;
	parse_table[SUBS_CMD][0] = &shift_group_cmd;
	parse_table[REDIRECTION][0] = &shift_r_command;
	parse_table[SUBSHELL][PIPE] = &reduce_pipe_command;
	parse_table[SUBSHELL][REDIRECTION] = &reduce_subshell;
	parse_table[SUBSHELL][OPERATOR] = &reduce_oper_command;
	parse_table[PIPE_CMD][SUBS_CMD] = &reduce_group_cmd;
	parse_table[OPERATOR_CMD][SUBS_CMD] = &reduce_group_cmd;
	parse_table[PIPE_CMD][GROUP_CMD] = &reduce_group_cmd;
	parse_table[OPERATOR_CMD][GROUP_CMD] = &reduce_group_cmd;
}

void	set_reduce_function(t_fptr **parse_table)
{
	parse_table[WORD][0] = &shift_w_ct;
	parse_table[CMD_TOKEN][0] = &shift_ct_command;
	parse_table[CMD_TOKEN][PIPE] = &shift_command;
	parse_table[CMD_TOKEN][REDIR_TOKEN] = &shift_command;
	parse_table[WORD][WORD] = &reduce_cmd_token;
	parse_table[COMMAND][REDIRECTION] = &reduce_command;
	parse_table[REDIRECTION][COMMAND] = &reduce_command;
	parse_table[COMMAND][PIPE] = &reduce_pipe_command;
	parse_table[COMMAND][OPERATOR] = &reduce_oper_command;
	parse_table[OPERATOR_CMD][COMMAND] = &reduce_command;
	parse_table[OPERATOR_CMD][OPERATOR_CMD] = &reduce_oper_command;
	parse_table[CMD_TOKEN][WORD] = &reduce_cmd_token;
	parse_table[COMMAND][COMMAND] = &reduce_command;
	parse_table[REDIR_TOKEN][WORD] = &reduce_redirection;
	parse_table[PIPE_CMD][COMMAND] = &reduce_command;
	parse_table[PIPE_CMD][PIPE_CMD] = &reduce_pipe_command;
	parse_table[REDIRECTION][REDIRECTION] = &reduce_redirection;
}

t_fptr	**init_parse_table(void)
{
	t_fptr	**parse_table;
	size_t	index;

	parse_table = (t_fptr **)ft_calloc((PIPE + 1), sizeof(t_fptr *));
	if (parse_table == NULL)
		exit_with_str("malloc error in init_parse_table", EXIT_FAILURE);
	index = 0;
	while (index < PIPE + 1)
	{
		parse_table[index] = (t_fptr *)ft_calloc((PIPE + 1), sizeof(t_fptr));
		if (parse_table[index] == NULL)
			exit_with_str("malloc error in init_parse_table", EXIT_FAILURE);
		++index;
	}
	set_reduce_function(parse_table);
	return (parse_table);
}
