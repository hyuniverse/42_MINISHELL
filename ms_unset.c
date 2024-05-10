/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siychoi <siychoi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 10:11:17 by siychoi           #+#    #+#             */
/*   Updated: 2024/05/10 12:42:42 by siychoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	del_key(t_envp **my_envp, char *key);
static int	check_unset_error(char *key);

int	ms_unset(t_envp **my_envp, char **argv)
{
	int	i;
	int	exit_code;

	i = 1;
	exit_code = 0;
	if (argv[1] != NULL)
	{		
		while (argv[i])
		{
			if (check_unset_error(argv[i]) == 0)
				del_key(my_envp, argv[i]);
			else
				exit_code = 1;
			i++;
		}
	}
	return (exit_code);
}

static int	check_unset_error(char *key)
{
	int	i;

	i = 0;
	if (ft_isalpha(key[i]) == 0)
		return (print_builtin_error("unset", key));
	while (key[++i])
	{
		if (ft_isalnum(key[i]) == 0)
			return (print_builtin_error("unset", key));
	}
	return (0);
}

static void	del_key(t_envp **my_envp, char *key)
{
	t_envp	*temp;
	t_envp	*n;
	int		lst_size;
	int		i;

	i = 0;
	lst_size = envp_size(my_envp);
	n = *my_envp;
	while (i < lst_size)
	{
		if (n->next != NULL)
		{
			if (ms_strncmp(n->next->key, key, ft_strlen(key)) == 0)
			{
				temp = n->next;
				n->next = n->next->next;
				free(temp->key);
				free(temp->value);
				free(temp);
				break ;
			}
		}
		n = n->next;
		i++;
	}
}
