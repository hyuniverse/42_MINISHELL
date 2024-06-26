/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehyupar <sehyupar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 17:44:32 by sehyupar          #+#    #+#             */
/*   Updated: 2024/06/26 14:31:40 by sehyupar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_signal(int signo, void *handler)
{
	struct sigaction	act;

	act.sa_handler = handler;
	sigaction(signo, &act, NULL);
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
