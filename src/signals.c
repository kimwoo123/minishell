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

#include "../inc/minishell.h"

#include <signal.h>
#include <termios.h>

#define CTRL_D		-1
#define BACKSPACE	127

#define SIGINT		2
#define SIGQUIT		3
#define SIGTERM		15

//signal, sigaction, sigemptyset, sigaddset
/******************************************************************************/
// void save_input_mode(void)
// {
// 	tcgetattr(STDIN_FILENO, &org_term);	// STDIN으로부터 터미널 속성을 받아온다
// }

// void set_input_mode(void)
// {
// 	tcgetattr(STDIN_FILENO, &new_term);				// STDIN으로부터 터미널 속성을 받아온다
// 	new_term.c_lflag &= ~(ICANON | ECHO);			// ICANON, ECHO 속성을 off
// 	new_term.c_cc[VMIN] = 1;						// 1 바이트씩 처리
// 	new_term.c_cc[VTIME] = 0;						// 시간은 설정하지 않음
// 	tcsetattr(STDIN_FILENO, TCSANOW, &new_term);	// 변경된 속성의 터미널을 STDIN에 바로 적용
// }

// void reset_input_mode(void)
// {
// 	tcsetattr(STDIN_FILENO, TCSANOW, &org_term);	// STDIN에 기존의 터미널 속성을 바로 적용
// }
/******************************************************************************/

static void	set_input_mode(void)
{
	struct termios	termios_p;

	// tcgetattr(STDIN_FILENO, &new_term);				// STDIN으로부터 터미널 속성을 받아온다
	// new_term.c_lflag &= ~(ICANON | ECHO);			// ICANON, ECHO 속성을 off
	// new_term.c_cc[VMIN] = 1;						// 1 바이트씩 처리
	// new_term.c_cc[VTIME] = 0;						// 시간은 설정하지 않음
	// tcsetattr(STDIN_FILENO, TCSANOW, &new_term);	// 변경된 속성의 터미널을 STDIN에 바로 적용
	
	if (tcgetattr(STDIN_FILENO, &termios_p) != 0)
		ft_perror("tcgetattr error", EXIT_FAILURE);
	termios_p.c_lflag &= ~ECHOCTL;
	if (tcsetattr(STDIN_FILENO, TCSANOW, &termios_p) != 0)
		ft_perror("tcsetattr error", EXIT_FAILURE);
}

static void	signal_handler(int signal_code)
{
	pid_t	pid;
	int		status;

	struct termios org_term;
	struct termios new_term;

	// // save_input_mode();		// 터미널 세팅 저장
	tcgetattr(STDIN_FILENO, &org_term);	// STDIN으로부터 터미널 속성을 받아온다
	// set_input_mode();

	pid = waitpid(-1, &status, WNOHANG);
	if (signal_code == SIGINT)
	{
		if (pid == -1)
		{
			rl_replace_line("", 0);
			write(STDIN_FILENO, "\n", 1);
			rl_on_new_line();
			rl_redisplay();
		}
		else
			write(STDIN_FILENO, "\n", 1);
	}
	else if (signal_code == SIGQUIT)
	{
		if (pid == -1)
		{
			rl_on_new_line();
			rl_redisplay();
			write(STDIN_FILENO, "  \b\b", 4);
		}
		else
			write(STDIN_FILENO, "Quit\n", 5);
	}
	// reset_input_mode();		// 터미널 세팅 초기화
	tcsetattr(STDIN_FILENO, TCSANOW, &org_term);	// STDIN에 기존의 터미널 속성을 바로 적용
}

void	set_signals(void)
{
	struct sigaction new_signal;
	struct sigaction old_signal;

	set_input_mode();
	new_signal.sa_handler = &signal_handler;
	new_signal.sa_flags = SA_RESTART; // 왜 되는건지 모름 ???????????
	sigemptyset(&new_signal.sa_mask);
	// sigemptyset(&new_signal.sa_mask);
	// sigaddset(&new_signal.sa_mask, SIGINT);
	// sigaddset(&new_signal.sa_mask, SIGQUIT);
	sigaction(SIGINT, &new_signal, &old_signal);
	sigaction(SIGQUIT, &new_signal, &old_signal);
}

// void	set_signal(void)
// {
// 	signal(SIGINT, signal_handler);		// C
// 	signal(SIGQUIT, signal_handler);	// Backslash
// 	// signal(SIGTERM, signal_handler);	// D
// }
