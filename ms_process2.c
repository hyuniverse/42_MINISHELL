/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_process2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siychoi <siychoi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 15:45:24 by siychoi           #+#    #+#             */
/*   Updated: 2024/06/26 15:48:40 by siychoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	set_process(t_envp **my_envp, t_input *input)
{
	t_fd		p;
	t_phrase	*phrase;
	int			last_code;
	int			i;

	i = 0;
	phrase = input->head;
	pipe(p.fd);
	first_process(my_envp, phrase, p);
	p.temp_fd = p.fd[0];
	close(p.fd[1]);
	while (i < input->cnt - 2)
	{
		phrase = phrase->next;
		pipe(p.fd);
		connect_process(my_envp, phrase, p);
		close(p.temp_fd);
		p.temp_fd = p.fd[0];
		close(p.fd[1]);
		i++;
	}
	phrase = input->tail;
	last_code = last_process(my_envp, phrase, p);
	close(p.fd[0]);
	return (wait_and_return(input, last_code));
}

int	make_pid(pid_t *pid)
{
	*pid = fork();
	if (*pid == -1)
		exit(1);
	return (*pid);
}

void	close_all_pipe(t_fd p)
{
	close(p.fd[0]);
	close(p.fd[1]);
	close(p.temp_fd);
}

void	dup_io_fd(int *io_fd, t_fd p)
{
	if (io_fd[0] == 0)
		dup2(p.temp_fd, 0);
	if (io_fd[1] == 1)
		dup2(p.fd[1], 1);
}

void	dup_and_close_last_process(int *io_fd, t_fd p)
{
	if (io_fd[0] == 0)
		dup2(p.temp_fd, 0);
	close(p.temp_fd);
}
