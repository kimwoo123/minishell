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
// 	// termios_p.c_lflag &= ~ECHOCTL;
// 	if (tcsetattr(STDIN_FILENO, TCSANOW, &termios_p) == FAILURE)
// 		exit_with_str("tcsetattr error in set input mode", EXIT_FAILURE);
// }

// static void	handle_signal(int signal_code)
// {
// 	pid_t	pid;

// 	pid = waitpid(-1, NULL, WNOHANG);
// 	if (signal_code == SIGINT)
// 	{
// 		if (pid == -1)
// 		{
// 			rl_replace_line("", 0);
// 			rl_on_new_line();
// 			rl_redisplay();
// 		}
		
// 		ft_putstr_fd("\n", STDIN_FILENO);
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
// }

// // static void	handle_signals(int signal_code)
// // {
// // 	pid_t			pid;
// // 	int				status;
// // 	struct termios	org_term;
// // 	// struct termios	new_term;

// // 	if (tcgetattr(STDIN_FILENO, &org_term) == FAILURE)
// // 		exit_with_str("tcgetattr error in set input mode", EXIT_FAILURE);
// // 	pid = waitpid(-1, &status, WNOHANG);
// // 	handle_signal(pid, signal_code);
// // 	if (tcsetattr(STDIN_FILENO, TCSANOW, &org_term) == FAILURE)
// // 		exit_with_str("tcsetattr error in set input mode", EXIT_FAILURE);
// // }

// void	set_signals(int	flag)
// {
// 	struct sigaction	new_signal;
// 	struct sigaction	old_signal;

// 	struct termios		new_term;
// 	struct termios		old_term;

// 	if (flag == 0) // setting
// 	{
// 		if (tcgetattr(STDIN_FILENO, &old_term) == FAILURE)
// 			exit_with_str("tcgetattr error in set input mode", EXIT_FAILURE);
// 		if (tcgetattr(STDIN_FILENO, &new_term) == FAILURE)
// 			exit_with_str("tcgetattr error in set input mode", EXIT_FAILURE);

// 		if (sigemptyset(&new_signal.sa_mask) == FAILURE)
// 			exit_with_str("sigemptyset error in set signal", EXIT_FAILURE);

// 		new_signal.sa_handler = &handle_signal;

// 		if (sigaction(SIGINT, &new_signal, &old_signal) == FAILURE)
// 			exit_with_str("sigaction error in set signal", EXIT_FAILURE);
// 		if (sigaction(SIGQUIT, &new_signal, &old_signal) == FAILURE)
// 			exit_with_str("sigaction error in set signal", EXIT_FAILURE);

// 		// new_signal.sa_flags = SA_RESTART;
// 		// new_term.c_lflag &= ~ECHO;
// 		// new_term.c_lflag &= ~ECHOCTL;

// 		if (tcsetattr(STDIN_FILENO, TCSANOW, &new_term) == FAILURE)
// 			exit_with_str("tcsetattr error in set input mode", EXIT_FAILURE);
// 	}
// 	else if (flag == 1) // setting
// 	{
		
// 		if (sigaction(SIGINT, NULL, NULL) == FAILURE)
// 			exit_with_str("sigaction error in set signal", EXIT_FAILURE);
// 		if (sigaction(SIGQUIT, NULL, NULL) == FAILURE)
// 			exit_with_str("sigaction error in set signal", EXIT_FAILURE);
// 		// if (tcsetattr(STDIN_FILENO, TCSANOW, &old_term) == FAILURE)
// 		// 	exit_with_str("tcsetattr error in set input mode", EXIT_FAILURE);
		
// 		return ;
// 	}
// 	else if (flag == 2)
// 	{
// 		if (sigaction(SIGINT, &new_signal, &old_signal) == FAILURE)
// 			exit_with_str("sigaction error in set signal", EXIT_FAILURE);
// 		if (sigaction(SIGQUIT, &new_signal, &old_signal) == FAILURE)
// 			exit_with_str("sigaction error in set signal", EXIT_FAILURE);
// 		// if (tcsetattr(STDIN_FILENO, TCSANOW, &new_term) == FAILURE)
// 		// 	exit_with_str("tcsetattr error in set input mode", EXIT_FAILURE);
		
// 		return ;
// 	}
// }

// static void	handle_signals(int signal_code)
// {
// 	pid_t			pid;
// 	int				status;
// 	struct termios	org_term;
// 	// struct termios	new_term;

// 	if (tcgetattr(STDIN_FILENO, &org_term) == FAILURE)
// 		exit_with_str("tcgetattr error in set input mode", EXIT_FAILURE);
// 	pid = waitpid(-1, &status, WNOHANG);
// 	handle_signal(pid, signal_code);
// 	if (tcsetattr(STDIN_FILENO, TCSANOW, &org_term) == FAILURE)
// 		exit_with_str("tcsetattr error in set input mode", EXIT_FAILURE);
// }

// void	set_input_mode(void)
// {
// 	struct termios	termios_p;

// 	if (tcgetattr(STDIN_FILENO, &termios_p) == FAILURE)
// 		exit_with_str("tcgetattr error in set input mode", EXIT_FAILURE);
// 	termios_p.c_lflag &= ~ECHOCTL;
// 	if (tcsetattr(STDIN_FILENO, TCSANOW, &termios_p) == FAILURE)
// 		exit_with_str("tcsetattr error in set input mode", EXIT_FAILURE);
// }

static void	handle_signal(int signal_code)
{
	pid_t	pid;

	pid = waitpid(-1, NULL, WNOHANG);
	if (signal_code == SIGINT)
	{
		if (pid == -1)
		{
			rl_replace_line("", 0);
			ft_putstr_fd("\n", STDERR_FILENO);
			rl_on_new_line();
			rl_redisplay();
		}
		else
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

void	set_signals(int flag)
{
	struct sigaction	new_signal;
	struct sigaction	old_signal;

	if (flag == 0)
	{
		// set_input_mode();
		new_signal.sa_handler = &handle_signal;
		// new_signal.sa_flags = SA_RESTART;
		// if (sigemptyset(&new_signal.sa_mask) == FAILURE)
		// 	exit_with_str("sigemptyset error in set signal", EXIT_FAILURE);
		if (sigaction(SIGINT, &new_signal, &old_signal) == FAILURE)
			exit_with_str("sigaction error in set signal", EXIT_FAILURE);
		if (sigaction(SIGQUIT, &new_signal, &old_signal) == FAILURE)
			exit_with_str("sigaction error in set signal", EXIT_FAILURE);
	}
	// else if (flag == 1)
	// {
	// 	new_signal.sa_handler = &handle_signal;
	// 	new_signal.sa_flags = SA_RESTART;
	// 	if (sigemptyset(&new_signal.sa_mask) == FAILURE)
	// 		exit_with_str("sigemptyset error in set signal", EXIT_FAILURE);
	// 	if (sigaction(SIGINT, &new_signal, &old_signal) == FAILURE)
	// 		exit_with_str("sigaction error in set signal", EXIT_FAILURE);
	// 	if (sigaction(SIGQUIT, &new_signal, &old_signal) == FAILURE)
	// 		exit_with_str("sigaction error in set signal", EXIT_FAILURE);
	// }
}

