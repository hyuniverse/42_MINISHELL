/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siychoi <siychoi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 17:44:10 by siychoi           #+#    #+#             */
/*   Updated: 2024/05/10 11:24:00 by siychoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ms_pwd(char **argv)
{
	char	*wd;

	wd = getcwd(NULL, 0);
	if (argv[1] != NULL)
	{
		if (argv[1][0] == '-' && argv[1][1] != '\0')
		{
			ft_putstr_fd("minishell: pwd can't have options\n", 2);
			return (1);
		}
	}
	else
		ft_putendl_fd(wd, 2);
	return (0);
}