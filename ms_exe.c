/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exe.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehyupar <sehyupar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 17:17:42 by siychoi           #+#    #+#             */
/*   Updated: 2024/06/27 19:37:07 by sehyupar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	make_list(t_input *list, t_envp**my_envp, char *buffer, int flag)
{
	int	process_code;

	add_history(buffer);
	if (!list)
	{
		process_code = 258;
		free(buffer);
		change_value(my_envp, "?", ft_itoa(process_code));
		return (0);
	}
	change_dollar_all_tokens(list, my_envp);
	redirection_to_filename(list, &flag);
	if (flag == TRUE)
	{
		flag = FALSE;
		process_code = 1;
	}
	else if (list->cnt == 1)
		process_code = exe_one_command(my_envp, list->head);
	else
		process_code = set_process(my_envp, list);
	change_value(my_envp, "?", ft_itoa(process_code));
	free(buffer);
	free_input(list);
	return (0);
}

void	exec_minishell(t_envp **my_envp)
{
	char			*buffer;
	t_input			*list;
	struct termios	old_term;
	int				flag;

	flag = FALSE;
	tcgetattr(STDIN_FILENO, &old_term);
	set_interactive_signal();
	while (1)
	{
		printf("minishell $ \033[s\b\b\b\b\b\b\b\b\b\b\b\b");
		buffer = readline("minishell$ ");
		if (buffer == NULL)
		{
			printf("\033[u\033[1B\033[1A\bexit\n");
			tcsetattr(STDIN_FILENO, TCSANOW, &old_term);
			exit(0);
		}
		else if (ft_strlen(buffer) != 0)
		{
			list = lexer(buffer);
			make_list(list, my_envp, buffer, flag);
		}
	}
}

int	exe_one_command(t_envp **my_envp, t_phrase *phrase)
{
	int	fd[4];
	int	return_code;

	fd[0] = 0;
	fd[1] = 1;
	if (check_process_error_return(phrase) == 0)
		return (0);
	else if (check_process_error_return(phrase) == 1)
		return (1);
	if (is_builtin_cmd(phrase))
	{
		fd[2] = dup(0);
		fd[3] = dup(1);
		if (open_in_and_out_fd(phrase, fd) != TRUE)
			return (errno);
		return_code = exe_only_builtin_cmd(my_envp, phrase);
		if (phrase->infile_type == 3)
			unlink(phrase->infile_name);
		dup2(fd[2], 0);
		dup2(fd[3], 1);
		return (return_code);
	}
	else
		return (exe_only_builtout_cmd(my_envp, phrase));
}

int	wait_and_return(t_input *list, int last_code)
{
	int	status;
	int	code;
	int	cnt;
	int	flag;

	cnt = 0;
	flag = 0;
	while (cnt < list->cnt)
	{
		if (wait(&status) == last_code)
		{
			if (WIFSIGNALED(status))
				code = WTERMSIG(status) + 128;
			else
				code = WEXITSTATUS(status);
		}
		if (WIFSIGNALED(status) && flag == 0)
		{
			print_signal_exit_status(WTERMSIG(status));
			flag++;
		}
		cnt++;
	}
	set_interactive_signal();
	return (code);
}

int	exe_only_builtout_cmd(t_envp **my_envp, t_phrase *phrase)
{
	pid_t	pid;
	char	**envp;
	int		status;
	int		io_fd[2];

	pid = fork();
	if (pid == 0)
	{
		set_child_signal();
		io_fd[0] = 0;
		io_fd[1] = 1;
		if (open_in_and_out_fd(phrase, io_fd) != TRUE)
			exit(errno);
		envp = envp_list_to_arr(*my_envp);
		return (child_process_exe(phrase, envp));
	}
	else if (pid == -1)
		exit(1);
	set_wait_signal();
	wait(&status);
	set_interactive_signal();
	if (WIFSIGNALED(status))
		return (print_signal_exit_status(WTERMSIG(status)));
	else
		return (WEXITSTATUS(status));
}
