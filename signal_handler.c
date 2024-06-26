/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehyupar <sehyupar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 14:28:52 by sehyupar          #+#    #+#             */
/*   Updated: 2024/06/26 14:32:08 by sehyupar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	catch_int(void)
{
	printf("\n");
	printf("minishell $ \033[s\b\b\b\b\b\b\b\b\b\b\b\b");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	catch_int_hd(void)
{
	printf("\n");
	exit(2);
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

int	print_signal_exit_status(int signo)
{
	if (signo == 2)
	{
		printf("\n");
		return (130);
	}
	else if (signo == 3)
	{
		printf("Quit: 3\n");
		return (131);
	}
	return (128 + signo);
}
