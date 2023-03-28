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

static void	handle_signal(pid_t pid, int signal_code)
{
	if (signal_code == SIGINT)
	{
		if (pid == -1)
		{
			rl_replace_line("", 0);
			ft_putstr_fd("\n", STDIN_FILENO);
			rl_on_new_line();
			rl_redisplay();
		}
		else
			ft_putstr_fd("\n", STDIN_FILENO);
	}
	else if (signal_code == SIGQUIT)
	{
		if (pid == -1)
		{
			rl_on_new_line();
			rl_redisplay();
			ft_putstr_fd("  \b\b", STDIN_FILENO);
		}
		else
			ft_putendl_fd("Quit", STDIN_FILENO);
	}
}

static void	handle_signals(int signal_code)
{
	pid_t			pid;
	struct termios	termios_p;

	tcgetattr(STDIN_FILENO, &termios_p);
	termios_p.c_lflag &= ~ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &termios_p);
	pid = waitpid(-1, NULL, WNOHANG);
	handle_signal(pid, signal_code);
}

void	set_signals(void)
{
	struct sigaction	new_signal;
	struct sigaction	old_signal;

	new_signal.sa_handler = &handle_signals;
	new_signal.sa_flags = SA_RESTART;
	if (sigemptyset(&new_signal.sa_mask) == FAILURE)
		exit_with_str("sigemptyset error in set signal", EXIT_FAILURE);
	if (sigaction(SIGINT, &new_signal, &old_signal) == FAILURE)
		exit_with_str("sigaction error in set signal", EXIT_FAILURE);
	if (sigaction(SIGQUIT, &new_signal, &old_signal) == FAILURE)
		exit_with_str("sigaction error in set signal", EXIT_FAILURE);
}
