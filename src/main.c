/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chajung <chajung@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 17:21:10 by chajung           #+#    #+#             */
/*   Updated: 2023/03/20 15:32:02 by wooseoki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_status;

int	main(int argc, char **argv, char **envp)
{
	t_data	data;
	char	*command_line;

	init_data(argc, argv, envp, &data);
	set_signals();
	while (1)
	{
		// printf("1: %d\n", g_status);
		command_line = readline("minishell> ");
		if (command_line == NULL)
			break ;
		add_history(command_line);
		run_minishell(&data, command_line);
		free (command_line);
		// system("leaks --list -- $PPID");
		// printf("2: %d\n", g_status);
	}
	ft_putendl_fd("bye", STDOUT_FILENO);
	return (0);
}
