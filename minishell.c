/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siychoi <siychoi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 17:24:50 by siychoi           #+#    #+#             */
/*   Updated: 2024/05/13 15:23:13 by siychoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//void	leaks(void)
//{
//	system("leaks minishell");
//}

int	main(int argc, char *argv[], char *envp[])
{
	char	*buffer;
	int		process_code;
	int		status;
	t_envp	*my_envp;

	//atexit(leaks);
	if (argc != 1 || argv[0] == NULL)
		exit(1);
	my_envp = NULL;
	envp_arr_to_list(envp, &my_envp);
	while (1)
	{
		buffer = readline("minishell$ ");
		if (buffer == NULL)
			exit(1);
		else if (ft_strlen(buffer) != 0)
		{		
			add_history(buffer);
			process_code = check_builtin_cmd(&my_envp, buffer);
			wait(&status);
			free(buffer);
			//'$?' 명령어 입력 시 process_code가 출력되어야함
		}
	}
	return (0);
}

int	check_builtin_cmd(t_envp **my_envp, char *cmd)
{
	char	**s_cmd;

	s_cmd = cmd_split(cmd);
	if (ms_strncmp(s_cmd[0], "cd", ft_strlen(cmd)) == 0)
		return (ms_cd(my_envp, s_cmd));
	else if (ms_strncmp(s_cmd[0], "echo", ft_strlen(cmd)) == 0)
		return (ms_echo(s_cmd));
	else if (ms_strncmp(s_cmd[0], "env", ft_strlen(cmd)) == 0)
		return (ms_env(my_envp, s_cmd));
	else if (ms_strncmp(s_cmd[0], "exit", ft_strlen(cmd)) == 0)
		return (ms_exit(s_cmd));
	else if (ms_strncmp(s_cmd[0], "export", ft_strlen(cmd)) == 0)
		return (ms_export(my_envp, s_cmd));
	else if (ms_strncmp(s_cmd[0], "pwd", ft_strlen(cmd)) == 0)
		return (ms_pwd(s_cmd));
	else if (ms_strncmp(s_cmd[0], "unset", ft_strlen(cmd)) == 0)
		return (ms_unset(my_envp, s_cmd));
	else
		return (child_process(cmd, my_envp));
}

int	child_process(char *cmd, t_envp **my_envp)
{
	int		fd[2];
	pid_t	pid;
	char	**envp;

	pipe(fd);
	pid = fork();
	if (pid == 0)
	{
		envp = envp_list_to_arr(my_envp);
		return (child_process_exe(cmd, envp));
	}
	else if (pid == -1)
		exit(1);
	return (0);
}

int	child_process_exe(char *cmd, char **envp)
{
	char	*path;
	char	**split_str;
	char	*temp;
	char	**s_cmd;

	s_cmd = cmd_split(cmd);
	path = find_path(envp);
	split_str = ft_split(path, ':');
	if (ft_strncmp(cmd, "./", 2) == 0 || ft_strchr(s_cmd[0], '/') != 0)
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
	return (print_code_error(127, cmd));
}
