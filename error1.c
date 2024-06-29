/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siychoi <siychoi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 13:06:36 by siychoi           #+#    #+#             */
/*   Updated: 2024/06/29 14:15:55 by siychoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	print_code_error(int code, char *cmd)
{
	if (code == 127)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd(": command not found\n", 2);
	}
	else if (code == 126)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd(": Permission denied\n", 2);
	}
	else
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(strerror(errno), 2);
		ft_putstr_fd("\n", 2);
	}
	exit(code);
}

int	print_code_error_builtin(int code, char *cmd)
{
	if (code == 127)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd(": command not found\n", 2);
	}
	else if (code == 126)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd(": permission denied\n", 2);
	}
	else
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(strerror(errno), 2);
		ft_putstr_fd("\n", 2);
	}
	return (code);
}

int	print_builtin_error(char *cmd, char *str)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": '", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
	return (1);
}

void	check_process_error(t_phrase *phrase)
{
	if (phrase->outfile_type == 6 || phrase->infile_type == 6)
		exit(1);
	if (phrase->head == NULL)
	{
		if (phrase->infile_type == 3)
			unlink(phrase->infile_name);
		free(phrase->infile_name);
		exit(0);
	}
}

int	check_process_error_return(t_phrase *phrase)
{
	if (phrase->outfile_type == 6 || phrase->infile_type == 6)
		return (1);
	if (phrase->head == NULL)
	{
		if (phrase->infile_type == 3)
			unlink(phrase->infile_name);
		return (0);
	}
	return (-1);
}
