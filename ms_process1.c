/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_process1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siychoi <siychoi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 15:39:14 by siychoi           #+#    #+#             */
/*   Updated: 2024/06/27 21:40:46 by siychoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	first_process(t_envp **my_envp, t_phrase *phrase, t_fd p)
{
	pid_t	pid;
	char	**envp;
	int		io_fd[2];

	if (make_pid(&pid) == 0)
	{
		set_child_signal();
		check_process_error(phrase);
		io_fd[0] = 0;
		io_fd[1] = 1;
		open_in_and_out_fd(phrase, io_fd);
		if (io_fd[1] == 1)
			dup2(p.fd[1], 1);
		close(p.fd[1]);
		close(p.fd[0]);
		if (is_builtin_cmd(phrase) == TRUE)
			exit(exe_only_builtin_cmd(my_envp, phrase));
		else
		{
			envp = envp_list_to_arr(*my_envp);
			child_process_exe(phrase, envp);
		}
	}
	else
		set_wait_signal();
}

void	connect_process(t_envp **my_envp, t_phrase *phrase, t_fd p)
{
	pid_t	pid;
	char	**envp;
	int		io_fd[2];

	if (make_pid(&pid) == 0)
	{
		set_child_signal();
		check_process_error(phrase);
		io_fd[0] = 0;
		io_fd[1] = 1;
		open_in_and_out_fd(phrase, io_fd);
		dup_io_fd(io_fd, p);
		close_all_pipe(p);
		if (is_builtin_cmd(phrase) == TRUE)
			exit(exe_only_builtin_cmd(my_envp, phrase));
		else
		{
			envp = envp_list_to_arr(*my_envp);
			child_process_exe(phrase, envp);
		}
	}
	else
		set_wait_signal();
}

int	last_process(t_envp **my_envp, t_phrase *phrase, t_fd p)
{
	pid_t	pid;
	char	**envp;
	int		io_fd[2];

	if (make_pid(&pid) == 0)
	{
		set_child_signal();
		check_process_error(phrase);
		io_fd[0] = 0;
		io_fd[1] = 1;
		open_in_and_out_fd(phrase, io_fd);
		dup_and_close_last_process(io_fd, p);
		if (is_builtin_cmd(phrase) == TRUE)
			exit(exe_only_builtin_cmd(my_envp, phrase));
		else
		{
			envp = envp_list_to_arr(*my_envp);
			return (child_process_exe(phrase, envp));
		}
	}
	else
	{
		set_wait_signal();
		return (pid);
	}
}

int	child_process_exe(t_phrase *phrase, char **envp)
{
	char		*path;
	char		**split_str;
	char		**cmd;
	struct stat	buf;

	cmd = token_to_arr(phrase);
	if (!cmd)
	{
		printf("geu cheo\n");
		return (0);
	}
	printf("cmd = %s\n", cmd[0]);
	path = find_path(envp);
	split_str = ft_split(path, ':');
	if (ft_strncmp(phrase->head->data, "./", 2) == 0 || \
		ft_strchr(cmd[0], '/') != 0)
	{
		stat(*cmd, &buf);
		if (S_ISDIR(buf.st_mode))
		{
			free_2d_array(cmd);
			return (print_dir_error(phrase->head->data));
		}
		if (access(cmd[0], F_OK) != 0)
			print_nofile_error(127, cmd[0]);
		else if (access(cmd[0], F_OK) == 0 && execve(cmd[0], cmd, envp) == -1)
			print_code_error(126, cmd[0]);
	}
	else
		child_process_exe2(split_str, cmd, envp);
	free_2d_array(cmd);
	return (print_code_error(127, phrase->head->data));
}

void	child_process_exe2(char **split_str, char **s_cmd, char **envp)
{
	char	*temp;

	while (*split_str)
	{
		if (*split_str[0] == '.')
		{
			split_str++;
			continue ;
		}
		temp = cmd_strjoin(*split_str, "/", s_cmd[0]);
		if (access(temp, X_OK) == 0 && execve(temp, s_cmd, envp) == -1)
			print_code_error(126, temp);
		split_str++;
		free(temp);
	}
}
