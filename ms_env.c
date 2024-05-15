/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siychoi <siychoi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 13:06:27 by siychoi           #+#    #+#             */
/*   Updated: 2024/05/09 21:28:18 by siychoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_env(t_envp **my_envp);

int	ms_env(t_envp **my_envp, char **argv)
{
	if (argv[1] == NULL)
		print_env(my_envp);
	else
	{
		ft_putstr_fd("minishell: env can't have arguments or options\n", 2);
		return (1);
	}
	return (0);
}

static void	print_env(t_envp **my_envp)
{
	int		lst_size;
	int		i;
	t_envp	*n;

	lst_size = envp_size(my_envp);
	i = 0;
	n = *my_envp;
	while (i < lst_size)
	{
		if (n->value != NULL)
		{
			ft_putstr_fd(n->key, 1);
			ft_putstr_fd("=", 1);
			ft_putstr_fd(n->value, 1);
			ft_putstr_fd("\n", 1);
		}
		i++;
		n = n->next;
	}
}
