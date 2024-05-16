/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_process.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siychoi <siychoi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 15:39:14 by siychoi           #+#    #+#             */
/*   Updated: 2024/05/16 17:07:38 by siychoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	set_process(t_envp **my_envp, t_input *list)
{
	t_fd	p;
	t_phrase	*phrase;
	int		last_code;
	int		i;

	i = 0;
	phrase = list->head;
	pipe(p.fd);
	first_process(my_envp, phrase, p);
	p.temp_fd = p.fd[0];
	close(p.fd[1]);
	while (i < list->cnt - 2)
	{
		pipe(p.fd);
		connect_process(my_envp, phrase, p);
		close(p.temp_fd);
		p.temp_fd = p.fd[0];
		close(p.fd[1]);
		i++;
		phrase = phrase->next;
	}
	phrase = list->tail;
	last_code = last_process(my_envp, phrase, p);
	close(p.fd[0]);
	return (wait_and_return(list, last_code));
}

void	first_process(t_envp **my_envp, t_phrase *phrase, t_fd p)
{
	pid_t	pid;
	char	**envp;

	pid = fork();
	if (pid == 0)
	{
		dup2(p.fd[1], 1);
		close(p.fd[1]);
		close(p.fd[0]);
		envp = envp_list_to_arr(my_envp);
		child_process_exe(phrase, envp);
	}
	else if (pid == -1)
		exit(1);
	else
		return ;
}

void	connect_process(t_envp **my_envp, t_phrase *phrase, t_fd p)
{
	pid_t	pid;
	char	**envp;

	pid = fork();
	if (pid == 0)
	{
		dup2(p.temp_fd, 0);
		dup2(p.fd[1], 1);
		close(p.fd[0]);
		close(p.fd[1]);
		close(p.temp_fd);
		envp = envp_list_to_arr(my_envp);
		child_process_exe(phrase, envp);
	}
	else if (pid == -1)
		exit(1);
}

int	last_process(t_envp **my_envp, t_phrase *phrase, t_fd p)
{
	pid_t	pid;
	char	**envp;

	pid = fork();
	if (pid == 0)
	{
		dup2(p.temp_fd, 0);
		close(p.temp_fd);
		envp = envp_list_to_arr(my_envp);
		return (child_process_exe(phrase, envp));
	}
	else if (pid == -1)
		exit(1);
	else
		return (pid);
}

int	child_process_exe(t_phrase *phrase, char **envp)
{
	char	*path;
	char	**split_str;
	char	*temp;
	char	**s_cmd;

	s_cmd = token_to_arr(phrase);
	path = find_path(envp);
	split_str = ft_split(path, ':');
	if (ft_strncmp(phrase->head->data, "./", 2) == 0 || ft_strchr(s_cmd[0], '/') != 0)
	{
		if (access(s_cmd[0], F_OK) == 0 && execve(s_cmd[0], s_cmd, envp) == -1)
			print_code_error(errno, s_cmd[0]);
	}
	else
	{
		while (*split_str)
		{
			temp = cmd_strjoin(*split_str, "/", s_cmd[0]);
			if (access(temp, X_OK) == 0 && execve(temp, s_cmd, envp) == -1)
				print_code_error(126, temp);
			split_str++;
			free(temp);
		}
	}
	return (print_code_error(127, phrase->head->data));
}
