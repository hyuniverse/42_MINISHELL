/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siychoi <siychoi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 17:24:50 by siychoi           #+#    #+#             */
/*   Updated: 2024/06/12 13:20:38 by siychoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//void	leaks(void)
//{
//	system("leaks minishell");
//}

int	main(int argc, char *argv[], char *envp[])
{
	t_envp	*my_envp;

	//atexit(leaks);
	if (argc != 1 || argv[0] == NULL)
		exit(1);
	my_envp = NULL;
	envp_arr_to_list(envp, &my_envp);
	exec_minishell(&my_envp);
	return (0);
}

void	exec_minishell(t_envp **my_envp)
{
	char			*buffer;
	int				process_code;
	t_input			*list;
	struct termios	old_term;
	int				flag;

	flag = FALSE;
	tcgetattr(STDIN_FILENO, &old_term);
	set_interactive_signal();
	while (1)
	{
		buffer = readline("minishell$ \033[s");
		if (buffer == NULL)
		{
			printf("\033[u\033[1B\033[1Aexit\n");
			tcsetattr(STDIN_FILENO, TCSANOW, &old_term);
			exit(0);
		}
		else if (ft_strlen(buffer) != 0)
		{
			list = lexer(buffer);
			add_history(buffer);
			redirection_to_filename(list, &flag);
			change_dollar_all_tokens(list, my_envp);
			if (flag == TRUE)
				flag = FALSE;
			else
			{
				if (list->cnt == 1)
					process_code = exe_one_command(my_envp, list->head);
				else
					process_code = set_process(my_envp, list);
			}
			free(buffer);
			free_input(list);
			change_value(my_envp, "?", ft_itoa(process_code));
		}
	}
}

int	exe_one_command(t_envp **my_envp, t_phrase *phrase)
{
	int	fd[4];
	int	return_code;

	fd[0] = 0;
	fd[1] = 1;
	if (phrase->head == NULL && phrase->infile_type == 3)
	{
		unlink(phrase->infile_name);
		return (0);
	}
	if (is_builtin_cmd(phrase))
	{
		fd[2] = dup(0);
		fd[3] = dup(1);
		if (open_in_and_out_fd(phrase, &fd[0], &fd[1]) != TRUE)
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
			code = WEXITSTATUS(status);
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

char	**token_to_arr(t_phrase *phrase)
{
	char	**result;
	int		i;
	int		cnt;
	t_token	*token;

	i = 0;
	cnt = 0;
	token = phrase->head;
	while (token != NULL)
	{
		cnt++;
		token = token->next;
	}
	result = (char **)malloc(sizeof(char *) * (cnt + 1));
	if (result == NULL)
		exit(1);
	token = phrase->head;
	while (i < cnt)
	{
		result[i] = ft_strdup(token->data);
		i++;
		token = token->next;
	}
	result[i] = NULL;
	return (result);
}

int	exe_only_builtout_cmd(t_envp **my_envp, t_phrase *phrase)
{
	pid_t	pid;
	char	**envp;
	int		status;
	int		infile_fd;
	int		outfile_fd;

	pid = fork();
	if (pid == 0)
	{
		set_child_signal();
		infile_fd = 0;
		outfile_fd = 1;
		if (open_in_and_out_fd(phrase, &infile_fd, &outfile_fd) != TRUE)
			exit(errno);
		envp = envp_list_to_arr(my_envp);
		return (child_process_exe(phrase, envp));
	}
	else if (pid == -1)
		exit(1);
	set_wait_signal();
	wait(&status);
	if (WIFSIGNALED(status))
		print_signal_exit_status(WTERMSIG(status));
	set_interactive_signal();
	return (WEXITSTATUS(status));
}
