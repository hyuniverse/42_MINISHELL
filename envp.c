/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siychoi <siychoi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 17:21:11 by siychoi           #+#    #+#             */
/*   Updated: 2024/06/07 16:55:30 by siychoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	envp_size(t_envp **my_envp)
{
	int		len;
	t_envp	*n;

	if (my_envp == NULL)
		return (0);
	len = 0;
	n = *my_envp;
	while (n->next != 0)
	{
		n = n->next;
		len++;
	}
	return (len + 1);
}

void	envp_add_back(t_envp **my_envp, t_envp *new)
{
	t_envp	*res;

	if (my_envp == NULL || new == NULL)
		return ;
	else if (*my_envp == NULL && new != NULL)
	{
		*my_envp = new;
		return ;
	}
	res = *my_envp;
	while ((*my_envp)->next != 0)
		*my_envp = (*my_envp)->next;
	(*my_envp)->next = new;
	*my_envp = res;
}

void	envp_arr_to_list(char **envp, t_envp **my_envp)
{
	int		i;
	int		j;
	int		idx;

	i = 0;
	while (envp[i])
	{
		j = 0;
		idx = 0;
		while (envp[i][j])
		{
			if (envp[i][j] == '=' && idx == 0)
				idx = j;
			j++;
		}
		add_key_and_value(my_envp, envp[i], idx);
		i++;
	}
}

char	**envp_list_to_arr(t_envp **my_envp)
{
	char	**result;
	int		i;
	int		lst_size;
	t_envp	*n;
	t_envp	*temp;

	i = 0;
	lst_size = envp_size(my_envp);
	result = (char **)malloc(sizeof(char *) * (lst_size + 1));
	if (result == NULL)
		exit(1);
	n = *my_envp;
	while (i < lst_size)
	{
		result[i] = cmd_strjoin(n->key, "=", n->value);
		i++;
		temp = n;
		n = n->next;
		free(temp->value);
		free(temp->key);
		free(temp);
	}
	result[i] = NULL;
	return (result);
}

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
