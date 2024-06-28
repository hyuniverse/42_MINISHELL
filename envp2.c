/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siychoi <siychoi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 20:11:22 by siychoi           #+#    #+#             */
/*   Updated: 2024/06/28 17:08:09 by siychoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	change_value(t_envp **my_envp, char *key, char *value)
{
	int		lst_size;
	int		i;
	t_envp	*n;

	i = 0;
	lst_size = envp_size(my_envp);
	n = *my_envp;
	while (i < lst_size)
	{
		if (ms_strncmp(n->key, key, ft_strlen(n->key)) == 0)
		{
			if (n->value != NULL)
				free(n->value);
			n->value = value;
			n->value_len = ft_strlen(n->value);
			break ;
		}
		i++;
		n = n->next;
	}
}

char	*find_key(t_envp **my_envp, char *str)
{
	int		lst_size;
	int		i;
	char	*key;
	t_envp	*n;

	i = 0;
	lst_size = envp_size(my_envp);
	key = NULL;
	n = *my_envp;
	while (i < lst_size)
	{
		if (ms_strncmp(n->key, str, ft_strlen(n->key)) == 0)
		{
			key = n->key;
			break ;
		}
		i++;
		n = n->next;
	}
	return (key);
}

char	*find_value(t_envp **my_envp, char *str)
{
	int		lst_size;
	int		i;
	char	*value;
	t_envp	*n;

	i = 0;
	lst_size = envp_size(my_envp);
	value = NULL;
	n = *my_envp;
	while (i < lst_size)
	{
		if (ms_strncmp(n->key, str, ft_strlen(n->key)) == 0)
		{
			value = ft_strdup(n->value);
			break ;
		}
		i++;
		n = n->next;
	}
	return (value);
}
