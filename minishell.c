/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehyupar <sehyupar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 17:24:50 by siychoi           #+#    #+#             */
/*   Updated: 2024/05/24 17:28:35 by sehyupar         ###   ########.fr       */
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

	tcgetattr(STDIN_FILENO, &old_term);
	set_interactive_signal();
	while (1)
	{
		buffer = readline("minishell$ ");
		if (buffer == NULL)
		{
			printf("\033[1A");
			printf("\033[11C");
			printf("exit\n");
			tcsetattr(STDIN_FILENO, TCSANOW, &old_term);
			exit(1);
		}
		else if (ft_strlen(buffer) != 0)
		{
			list = lexer(buffer);
			add_history(buffer);
			if (list->cnt == 1)
				process_code = exe_one_command(my_envp, list->head);
			else
				process_code = set_process(my_envp, list);
			free(buffer);
			free_input(list);
			//'$?' 명령어 입력 시 process_code가 출력되어야함
		}
	}
}

int	exe_one_command(t_envp **my_envp, t_phrase *phrase)
{
	if (is_builtin_cmd(phrase))
		return (exe_only_builtin_cmd(my_envp, phrase));
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
	t_token	*token;

	i = 0;
	result = (char **)malloc(sizeof(char *) * (phrase->cnt + 1));
	if (result == NULL)
		exit(1);
	token = phrase->head;
	while (i < phrase->cnt)
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

	pid = fork();
	if (pid == 0)
	{
		set_child_signal();
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
	return (0);
}
