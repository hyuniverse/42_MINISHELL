/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_redirection2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siychoi <siychoi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 16:31:03 by siychoi           #+#    #+#             */
/*   Updated: 2024/06/28 21:48:51 by siychoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	infile_to_filename(t_phrase *phrase, t_token *token, int *flag)
{
	if (phrase->infile_name != NULL)
		free(phrase->infile_name);
	if (token->type == HD)
	{
		if (phrase->infile_name != NULL && ft_strncmp(phrase->infile_name, \
		"/Users/siychoi/temp/.heredoc", 28) == 0)
			unlink(phrase->infile_name);
		phrase->infile_name = make_hd_file(token, flag);
		if (*flag == TRUE)
			return (FALSE);
		phrase->infile_type = HD;
	}
	else
	{
		phrase->infile_name = ft_strdup(token->data);
		phrase->infile_type = IN;
		if (is_input_error(token) == 1)
		{
			phrase->infile_type = ERROR;
			print_code_error_builtin(0, token->data);
			return (FALSE);
		}
	}
	return (TRUE);
}

int	outfile_to_filename(t_phrase *phrase, t_token *token)
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
		print_code_error_builtin(0, token->data);
		return (FALSE);
	}
	return (TRUE);
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
			if (check_rd_error(phrase, token, flag) == FALSE)
				break ;
			token = token->next;
		}
		skip_redirection(phrase);
		phrase = phrase->next;
	}
}

int	check_rd_error(t_phrase *phrase, t_token *token, int *flag)
{
	if (token->type == IN || token->type == HD)
	{
		if (infile_to_filename(phrase, token, flag) == FALSE)
		{
			if (phrase->infile_name != NULL)
				free(phrase->infile_name);
			//if (phrase->outfile_name)
			//	free(phrase->outfile_name);
			return (FALSE);
		}
	}
	else if (token->type == OUT || token->type == APD)
	{
		if (outfile_to_filename(phrase, token) == FALSE)
		{
			if (phrase->outfile_name != NULL)
				free(phrase->outfile_name);
			return (FALSE);
		}
	}
	return (TRUE);
}

void	check_heredoc_exit(t_token *token, char *buffer)
{
	if (buffer == NULL)
	{
		printf("\033[1u\033[1B\033[1A");
		free(token->data);
		exit(1);
	}
}
