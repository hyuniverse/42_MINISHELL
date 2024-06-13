/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_redirection.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siychoi <siychoi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 09:41:29 by siychoi           #+#    #+#             */
/*   Updated: 2024/06/13 15:27:21 by siychoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	skip_redirection(t_phrase *phrase)
{
	t_token	*token;

	token = phrase->head;
	while (token != NULL && token->type != 1)
		token = token->next;
	phrase->head = token;
}

void	redirection_to_filename(t_input *input, int *flag)
{
	t_phrase	*phrase;
	t_token		*token;

	phrase = input->head;
	while (phrase != NULL && *flag == FALSE)
	{
		token = phrase->head;
		while (token != NULL && token->type != CNT)
		{
			if (token->type == IN || token->type == HD)
			{
				if (phrase->infile_name != NULL)
					free(phrase->infile_name);
				if (token->type == HD)
				{
					if (phrase->infile_name != NULL && ft_strncmp(phrase->infile_name, "/Users/siychoi/temp/.heredoc", 28) == 0)
						unlink(phrase->infile_name);
					phrase->infile_name = make_hd_file(token, flag);
					if (*flag == TRUE)
						break;
					phrase->infile_type = HD;
				}
				else
				{
					phrase->infile_name = ft_strdup(token->data);
					phrase->infile_type = IN;
					if (is_input_error(token) == 1)
					{
						phrase->infile_type = ERROR;
						ft_putstr_fd("minishell: ", 2);
						ft_putstr_fd(token->data, 2);
						ft_putstr_fd(": ", 2);
						ft_putstr_fd(strerror(errno), 2);
						ft_putstr_fd("\n", 2);
						break ;
					}
				}
			}
			else if (token->type == OUT || token->type == APD)
			{
				if (phrase->outfile_name != NULL)
					free(phrase->outfile_name);
				if (token->type == OUT)
					phrase->outfile_type = OUT;
				else if (token->type == APD)
					phrase->outfile_type = APD;
				phrase->outfile_name = ft_strdup(token->data);
				if (is_output_error(token) == 1)
				{
					phrase->outfile_type = ERROR;
					ft_putstr_fd("minishell: ", 2);
					ft_putstr_fd(token->data, 2);
					ft_putstr_fd(": ", 2);
					ft_putstr_fd(strerror(errno), 2);
					ft_putstr_fd("\n", 2);
					break ;
				}
			}
			token = token->next;
		}
		skip_redirection(phrase);
		phrase = phrase->next;
	}
}

int	is_input_error(t_token *token)
{
	int	in_fd;
	int	error_flag;

	in_fd = 0;
	error_flag = 0;
	if (token->type == 2)
		in_fd = open(token->data, O_RDONLY, 0644);
	if (in_fd < 0)
		error_flag = 1;
	if (in_fd > 0)
		close(in_fd);
	return (error_flag);
}

int	is_output_error(t_token *token)
{
	int	out_fd;
	int	error_flag;

	out_fd = 0;
	error_flag = 0;
	if (token->type == 4)
		out_fd = open(token->data, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	else if (token->type == 5)
		out_fd = open(token->data, O_WRONLY | O_APPEND | O_CREAT, 0644);
	if (out_fd < 0)
		error_flag = 1;
	if (out_fd > 0)
		close(out_fd);
	return (error_flag);
}

char	*make_hd_file(t_token *token, int *flag)
{
	int		fd;
	char	*path;
	int		status;

	path = ft_substr("/Users/siychoi/temp/.heredoc1", 0, 30);
	while (1)
	{
		if (access(path, F_OK) == 0)
			path = ft_strjoin(path, "1");
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

	pid = fork();
	if (pid == 0)
	{
		set_hd_signal();
		while (1)
		{
			buffer = readline("> \033[s");
			if (buffer == NULL)
			{
				printf("\033[1u\033[1B\033[1A");
				exit(1);
			}
			if (ms_strncmp(buffer, token->data, ft_strlen(buffer)) == 0)
				break ;
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

int	open_in_and_out_fd(t_phrase *phrase, int *infile_fd, int *outfile_fd)
{
	if (phrase->infile_name != NULL)
	{
		*infile_fd = open(phrase->infile_name, O_RDONLY);
		if (*infile_fd < 0)
		{
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(phrase->infile_name, 2);
			ft_putstr_fd(": ", 2);
			ft_putstr_fd(strerror(errno), 2);
			ft_putstr_fd("\n", 2);
			return (errno);
		}
		dup2(*infile_fd, 0);
		close(*infile_fd);
	}
	if (phrase->outfile_name != NULL)
	{
		if (phrase->outfile_type == 4)
			*outfile_fd = open(phrase->outfile_name, O_WRONLY | O_TRUNC | O_CREAT, 0644);
		else if (phrase->outfile_type == 5)
			*outfile_fd = open(phrase->outfile_name, O_WRONLY | O_APPEND | O_CREAT, 0644);
		if (*outfile_fd < 0)
		{
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(phrase->outfile_name, 2);
			ft_putstr_fd(": ", 2);
			ft_putstr_fd(strerror(errno), 2);
			ft_putstr_fd("\n", 2);
			return (errno);
		}
		dup2(*outfile_fd, 1);
		close(*outfile_fd);
	}
	return (TRUE);
}
