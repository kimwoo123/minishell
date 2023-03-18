/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_table.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wooseoki <wooseoki@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 15:27:38 by wooseoki          #+#    #+#             */
/*   Updated: 2023/03/18 16:00:39 by wooseoki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_reduce_function(t_fptr **reduce_table)
{
	reduce_table[CMD_TOKEN][0] = shift_ct_command;
	reduce_table[WORD][0] = shift_w_ct;
	reduce_table[REDIRECTION][0] = shift_r_command;
	reduce_table[CMD_TOKEN][REDIR_TOKEN] = shift_command;
	reduce_table[CMD_TOKEN][PIPE] = shift_command;
	reduce_table[REDIR_TOKEN][WORD] = reduce_redirection;
	reduce_table[REDIRECTION][REDIRECTION] = reduce_redirection;
	reduce_table[WORD][WORD] = reduce_cmd_token;
	reduce_table[CMD_TOKEN][WORD] = reduce_cmd_token;
	reduce_table[COMMAND][COMMAND] = reduce_command;
	reduce_table[PIPE_CMD][COMMAND] = reduce_command;
	reduce_table[COMMAND][PIPE] = reduce_pipe_command;
	reduce_table[PIPE_CMD][PIPE_CMD] = reduce_pipe_command;
}

t_fptr	**init_reduce_functions(void)
{
	t_fptr	**reduce_table;
	size_t	index;

	reduce_table = (t_fptr **)ft_calloc((PIPE + 1), sizeof(t_fptr *));
	if (!reduce_table)
		return (NULL);
	index = 0;
	while (index < PIPE + 1)
	{
		reduce_table[index] = (t_fptr *)ft_calloc((PIPE + 1), sizeof(t_fptr));
		++index;
	}
	set_reduce_function(reduce_table);
	return (reduce_table);
}
