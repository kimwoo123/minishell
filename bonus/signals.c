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

// static void	set_input_mode(void)
// {
// 	struct termios	termios_p;

// 	if (tcgetattr(STDIN_FILENO, &termios_p) == FAILURE)
// 		exit_with_str("tcgetattr error in set input mode", EXIT_FAILURE);
// 	termios_p.c_lflag &= ~ECHOCTL;
// 	if (tcsetattr(STDIN_FILENO, TCSANOW, &termios_p) == FAILURE)
// 		exit_with_str("tcsetattr error in set input mode", EXIT_FAILURE);
// }

// static void signal_handler(int signo)
// {
// 	pid_t   pid;

// 	set_signal();
// 	pid = waitpid(-1, NULL, WNOHANG);
// 	if (signo == SIGINT)
// 	{
// 		rl_redisplay();
// 		rl_replace_line("", 0);
// 		if (pid == -1)
// 			ft_printf("\b\b\b\b\b\b\n");
// 		else
// 			ft_printf("\n");
// 		// exit_code_export(1);
// 	}
// 	if (signo == SIGTERM)
// 		exit(0);
// }

// static void	handle_signal(int signal_code)
// {
// 	pid_t	pid;

// 	pid = waitpid(-1, NULL, WNOHANG);
// 	if (signal_code == SIGINT)
// 	{
// 		rl_redisplay();
// 		rl_replace_line("", 0);
// 		if (pid == -1)
// 			ft_putstr_fd("\b\b\b\b\b\b\n", STDIN_FILENO);
// 		else
// 			ft_putstr_fd("\n", STDIN_FILENO);
// 		// exit_code_export(1);
// 	}
// 	else if (signal_code == SIGQUIT)
// 	{
// 		if (pid == -1)
// 		{
// 			rl_on_new_line();
// 			rl_redisplay();
// 			ft_putstr_fd("  \b\b", STDIN_FILENO);
// 		}
// 		else
// 			ft_putendl_fd("Quit", STDIN_FILENO);
// 	}
// 	else if (signal_code == SIGTERM)
// 		exit(EXIT_SUCCESS);
// }

// static void	handle_signals(int signal_code)
// {
// 	// pid_t			pid;
// 	// int				status;
// 	struct termios	org_term;
// 	// struct termios	new_term;

// 	if (tcgetattr(STDIN_FILENO, &org_term) == FAILURE)
// 		exit_with_str("tcgetattr error in set input mode", EXIT_FAILURE);
// 	// pid = waitpid(-1, &status, WNOHANG);
// 	// handle_signal(pid, signal_code);
// 	handle_signal(signal_code);
// 	if (tcsetattr(STDIN_FILENO, TCSANOW, &org_term) == FAILURE)
// 		exit_with_str("tcsetattr error in set input mode", EXIT_FAILURE);
// }

// void	initialize_sig(struct sigaction new_signal, struct sigaction old_signal)
// {
// 	if (sigemptyset(&new_signal.sa_mask) == FAILURE)
// 		exit_with_str("sigemptyset error in set signal", EXIT_FAILURE);
// 	if (sigaction(SIGINT, &old_signal, NULL) == FAILURE)
// 		exit_with_str("sigaction error in set signal", EXIT_FAILURE);
// 	if (sigaction(SIGQUIT, &old_signal, NULL) == FAILURE)
// 		exit_with_str("sigaction error in set signal", EXIT_FAILURE);
// }

// void	reset_signals(void)
// {
// 	struct sigaction	old_signal;

// 	if (sigaction(SIGINT, &old_signal, NULL) == FAILURE)
// 		exit_with_str("sigaction error in set signal", EXIT_FAILURE);
// 	if (sigaction(SIGQUIT, &old_signal, NULL) == FAILURE)
// 		exit_with_str("sigaction error in set signal", EXIT_FAILURE);
// 	if (sigaction(SIGTERM, &old_signal, NULL) == FAILURE)
// 		exit_with_str("sigaction error in set signal", EXIT_FAILURE);
// }

static void	handle_signal(int signal_code)
{
	pid_t	pid;

	// set_signal();
	pid = waitpid(-1, NULL, WNOHANG);
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
	else if (signal_code == SIGTERM)
		exit(EXIT_SUCCESS);
}

void	set_signals(void)
{
	struct sigaction	new_signal;
	struct sigaction	old_signal;
 
	// set_input_mode();
	new_signal.sa_handler = &handle_signal;
	// new_signal.sa_flags = SA_RESTART;
	if (sigemptyset(&new_signal.sa_mask) == FAILURE)
		exit_with_str("sigemptyset error in set signal", EXIT_FAILURE);
	if (sigaction(SIGINT, &new_signal, &old_signal) == FAILURE)
		exit_with_str("sigaction error in set signal", EXIT_FAILURE);
	if (sigaction(SIGQUIT, &new_signal, &old_signal) == FAILURE)
		exit_with_str("sigaction error in set signal", EXIT_FAILURE);
	if (sigaction(SIGTERM, &new_signal, &old_signal) == FAILURE)
		exit_with_str("sigaction error in set signal", EXIT_FAILURE);
}
