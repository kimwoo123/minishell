/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chajung <chajung@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 10:45:25 by chajung           #+#    #+#             */
/*   Updated: 2023/03/05 10:45:27 by chajung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

static void	handle_signal(int signal_code)
{
	pid_t	pid;

	pid = waitpid(-1, NULL, WNOHANG);
	if (signal_code == SIGINT)
	{
		if (pid == -1)
		{
			rl_replace_line("", 0);
			rl_on_new_line();
			rl_redisplay();
		}
		ft_putstr_fd("\n", STDERR_FILENO);
	}
	else if (signal_code == SIGQUIT)
	{
		if (pid == -1)
		{
			rl_on_new_line();
			rl_redisplay();
			ft_putstr_fd("  \b\b", STDERR_FILENO);
		}
		else
			ft_putendl_fd("Quit", STDERR_FILENO);
	}
}

void	set_signals(void)
{
	struct sigaction	new_signal;
	struct sigaction	old_signal;

	new_signal.sa_handler = &handle_signal;
	new_signal.sa_flags = SA_RESTART;
	if (sigemptyset(&new_signal.sa_mask) == FAILURE)
		exit_with_str("sigemptyset error in set signal", EXIT_FAILURE);
	if (sigaction(SIGINT, &new_signal, &old_signal) == FAILURE)
		exit_with_str("sigaction error in set signal", EXIT_FAILURE);
	if (sigaction(SIGQUIT, &new_signal, &old_signal) == FAILURE)
		exit_with_str("sigaction error in set signal", EXIT_FAILURE);
}
