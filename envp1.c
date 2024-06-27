/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siychoi <siychoi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 17:21:11 by siychoi           #+#    #+#             */
/*   Updated: 2024/06/27 20:15:37 by siychoi          ###   ########.fr       */
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
	add_key_and_value(my_envp, "?=0", 1);
}

char	**envp_list_to_arr(t_envp *my_envp)
{
	char	**result;
	t_envp	*temp;
	int		i;

	i = 0;
	result = (char **)malloc(sizeof(char *) * (envp_size(&my_envp) + 1));
	if (result == NULL)
		exit(1);
	while (my_envp)
	{	
		if (my_envp->value != NULL)
			result[i] = cmd_strjoin(my_envp->key, "=", my_envp->value);
		else
			result[i] = ft_strdup(my_envp->key);
		temp = my_envp;
		my_envp = my_envp->next;
		if (temp->value != NULL)
			free(temp->value);
		free(temp->key);
		free(temp);
		i++;
	}
	result[i] = NULL;
	return (result);
}