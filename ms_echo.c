/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siychoi <siychoi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 13:17:59 by siychoi           #+#    #+#             */
/*   Updated: 2024/05/10 12:38:17 by siychoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_n_option(char *str);
static void	echo_yes_options(char **argv, int i);
static void	echo_no_options(char **argv);

int	ms_echo(char **argv)
{
	int	i;
	int	flag;

	flag = 0;
	i = 1;
	if (argv[1] == NULL)
	{
		ft_putstr_fd("\n", 1);
		return (0);
	}
	while (argv[i])
	{
		if (is_n_option(argv[i]) == 0)
			break ;
		flag = 1;
		i++;
	}
	if (flag == 0)
		echo_no_options(argv);
	else
		echo_yes_options(argv, i);
	return (0);
}

static int	is_n_option(char *str)
{
	if (*str != '-')
		return (0);
	str++;
	while (*str)
	{
		if (*str != 'n')
			return (0);
		str++;
	}
	return (1);
}

static void	echo_yes_options(char **argv, int i)
{
	if (argv[i] == NULL)
		ft_putstr_fd("", 1);
	while (argv[i])
	{
		ft_putstr_fd(argv[i], 1);
		if (argv[i + 1] != NULL)
			ft_putstr_fd(" ", 1);
		i++;
	}
}

static void	echo_no_options(char **argv)
{
	int	i;

	i = 1;
	while (argv[i])
	{
		ft_putstr_fd(argv[i], 1);
		ft_putstr_fd(" ", 1);
		i++;
	}
	ft_putstr_fd("\n", 1);
}

int	str_str_len(char **str)
{
	int	len;

	len = 0;
	if (str == NULL)
		return (len);
	while (str[len])
		len++;
	return (len);
}
