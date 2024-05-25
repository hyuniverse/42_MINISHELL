/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_redirection.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siychoi <siychoi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 09:41:29 by siychoi           #+#    #+#             */
/*   Updated: 2024/05/25 14:18:51 by siychoi          ###   ########.fr       */
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

void	redirection_to_filename(t_phrase *phrase)
{
	t_token		*token;
	
	token = phrase->head;
	while (token != NULL && token->type != 1)
	{
		if (token->type == 2 || token->type == 3)
		{
			if (phrase->infile_name != NULL)
				free(phrase->infile_name);
			if (token->type == 3)
			{
				if (phrase->infile_name != NULL && ft_strncmp(phrase->infile_name, "/Users/siychoi/temp/.heredoc", 28) == 0)
					unlink(phrase->infile_name);
				phrase->infile_name = make_hd_file(token);
			}
			else
				phrase->infile_name = ft_strdup(token->data);
			if (token->type == 4 && access(token->data, R_OK != 0))
				break ;
		}
		else if (token->type == 4 || token->type == 5)
		{
			if (phrase->outfile_name != NULL)
				free(phrase->outfile_name);
			phrase->outfile_name = ft_strdup(token->data);
			if (is_output_error(token) == 1)
				break ;
		}
		token = token->next;
	}
	skip_redirection(phrase);
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

char	*make_hd_file(t_token *token)
{
	int		fd;
	char	*path;
	char	*buffer;

	path = ft_substr("/Users/siychoi/temp/.heredoc1", 0, 30);
	while (1)
	{
		if (access(path, F_OK) == 0)
			path = ft_strjoin(path, "1");
		else
		{
			fd = open(path, O_WRONLY | O_TRUNC | O_CREAT, 0644);
			break;
		}
	}
	while (1)
	{
		buffer = readline("> ");
		if (buffer == NULL)
			exit(1);
		if (ms_strncmp(buffer, token->data, ft_strlen(buffer)) == 0)
			break;
		ft_putendl_fd(buffer, fd);
		free(buffer);
	}
	close(fd);
	return (path);
}

int	open_in_out_fd(t_phrase *phrase, int *infile_fd, int *outfile_fd)
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
		*outfile_fd = open(phrase->outfile_name, O_WRONLY | O_TRUNC | O_CREAT, 0644);
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
