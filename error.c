/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehyupar <sehyupar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 13:06:36 by siychoi           #+#    #+#             */
/*   Updated: 2024/06/12 20:08:04 by sehyupar         ###   ########.fr       */
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
