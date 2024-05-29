/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehyupar <sehyupar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 17:44:32 by sehyupar          #+#    #+#             */
/*   Updated: 2024/05/29 15:26:36 by sehyupar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	catch_int(void)
{
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0); // undolist 삭제..?유지..?
	rl_redisplay();
}

void	catch_int_hd(void)
{
	printf("\n");
	exit(1);
}

void	set_signal(int signo, void *handler)
{
	struct sigaction	act;

	act.sa_handler = handler;
	sigaction(signo, &act, NULL);
}


void	echo_ctrl(void)
{
	struct termios	term;

	tcgetattr(STDIN_FILENO, &term);
	term.c_lflag &= ~ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
}

void	display_ctrl(void)
{
	struct termios	term;

	tcgetattr(STDIN_FILENO, &term);
	term.c_lflag |= ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
}

void	set_interactive_signal(void)
{
	echo_ctrl();
	set_signal(SIGINT, &catch_int);
	set_signal(SIGQUIT, SIG_IGN);
}

void	set_wait_signal(void)
{
	set_signal(SIGINT, SIG_IGN);
}

void	set_child_signal(void)
{
	display_ctrl();
	set_signal(SIGINT, SIG_DFL);
	set_signal(SIGQUIT, SIG_DFL);
}

void	set_hd_signal(void)
{
	set_signal(SIGINT, &catch_int_hd);
}

void	print_signal_exit_status(int signo)
{
	if (signo == 2)
		printf("\n");
	else if (signo == 3)
		printf("Quit: 3\n");
	return ;
}
