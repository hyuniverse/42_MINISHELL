/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siychoi <siychoi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 14:34:58 by siychoi           #+#    #+#             */
/*   Updated: 2024/06/26 16:29:05 by siychoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_syntax_error(char	*ptr)
{
	ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
	if (!*ptr)
		ft_putstr_fd("newline", 2);
	else if (ft_strncmp(ptr, "|", 1) == 0)
		ft_putstr_fd("|", 2);
	else if (ft_strncmp(ptr, ">>", 2) == 0)
		ft_putstr_fd(">>", 2);
	else if (ft_strncmp(ptr, ">", 1) == 0)
		ft_putstr_fd(">", 2);
	else if (ft_strncmp(ptr, "<<", 2) == 0)
		ft_putstr_fd("<<", 2);
	else if (ft_strncmp(ptr, "<", 1) == 0)
		ft_putstr_fd("<", 2);
	ft_putstr_fd("'\n", 2);
}

int	print_dir_error(char *cmd)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": is a directory\n", 2);
	exit(126);
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
