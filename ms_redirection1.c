/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_redirection1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siychoi <siychoi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 09:41:29 by siychoi           #+#    #+#             */
/*   Updated: 2024/06/27 22:06:25 by siychoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	skip_redirection(t_phrase *phrase)
{
	t_token	*token;
	t_token	*next;

	token = phrase->head;
	while (token != NULL && token->type != 1)
	{
		next = token->next;
		free(token->data);
		free(token);
		token = next;
	}
	phrase->head = token;
}

char	*make_hd_file(t_token *token, int *flag)
{
	int		fd;
	char	*path;
	char	*temp;
	int		status;

	path = ft_substr("/Users/siychoi/temp/.heredoc1", 0, 30);
	while (1)
	{
		if (access(path, F_OK) == 0)
		{
			temp = path;
			path = ft_strjoin(path, "1");
			free(temp);
		}
		else
			break ;
	}
	fd = open(path, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	make_hd_content(token, fd);
	wait(&status);
	if (WEXITSTATUS(status) == 2)
		*flag = TRUE;
	set_interactive_signal();
	close(fd);
	return (path);
}

void	make_hd_content(t_token *token, int fd)
{
	pid_t	pid;
	char	*buffer;

	if (make_pid(&pid) == 0)
	{
		set_hd_signal();
		while (1)
		{
			printf("> \033[s\b\b");
			buffer = readline("> ");
			if (buffer == NULL)
			{
				printf("\033[1u\033[1B\033[1A");
				free(token->data);
				exit(1);
			}
			if (ms_strncmp(buffer, token->data, ft_strlen(buffer)) == 0)
			{
				free(buffer);
				break ;
			}
			ft_putendl_fd(buffer, fd);
			free(buffer);
		}
		close(fd);
		exit(1);
	}
	else if (pid == -1)
		exit(1);
	set_signal(SIGINT, SIG_IGN);
}

void	open_outfile(t_phrase *phrase, int *io_fd)
{
	if (phrase->outfile_type == 4)
		io_fd[1] = \
		open(phrase->outfile_name, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	else if (phrase->outfile_type == 5)
		io_fd[1] = \
		open(phrase->outfile_name, O_WRONLY | O_APPEND | O_CREAT, 0644);
}

int	open_in_and_out_fd(t_phrase *phrase, int *io_fd)
{
	if (phrase->infile_name != NULL)
	{
		io_fd[0] = open(phrase->infile_name, O_RDONLY);
		if (io_fd[0] < 0)
		{
			print_code_error_builtin(0, phrase->infile_name);
			return (errno);
		}
		dup2(io_fd[0], 0);
		close(io_fd[0]);
	}
	if (phrase->outfile_name != NULL)
	{
		open_outfile(phrase, io_fd);
		if (io_fd[1] < 0)
		{
			print_code_error_builtin(0, phrase->outfile_name);
			return (errno);
		}
		dup2(io_fd[1], 1);
		close(io_fd[1]);
	}
	return (TRUE);
}
