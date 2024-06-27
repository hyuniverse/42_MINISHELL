/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehyupar <sehyupar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 20:34:36 by siychoi           #+#    #+#             */
/*   Updated: 2024/06/27 14:51:42 by sehyupar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	add_envp(t_envp **my_envp, char *str);

int	ms_export(t_envp **my_envp, char **argv)
{
	int		i;
	int		exit_code;

	i = 1;
	exit_code = 0;
	if (argv[1] == NULL)
		print_envp(my_envp);
	else
	{
		while (argv[i])
		{
			exit_code += add_envp(my_envp, argv[i]);
			i++;
		}
	}
	if (exit_code > 0)
		exit_code = 1;
	free_2d_array(argv);
	return (exit_code);
}

static int	add_envp(t_envp **my_envp, char *s)
{
	int		i;
	int		j;
	char	*key;

	i = 0;
	j = 0;
	if (ft_isalpha(s[i]) == 0)
		return (print_builtin_error("envp", s));
	while (s[++i])
	{
		if (j == 0 && ft_isalnum(s[i]) == 0 && s[i] != '=')
			return (print_builtin_error("envp", s));
		else if (s[i] == '=' && j == 0)
			j = i;
	}
	if (j == 0)
		key = ft_strdup(s);
	else
		key = ft_substr(s, 0, j);
	if (find_key(my_envp, key) == NULL)
		add_key_and_value(my_envp, s, j);
	else if (j != 0)
		change_value(my_envp, key, ft_substr(s, j + 1, ft_strlen(s) - j - 1));
	free(key);
	return (0);
}

void	add_key_and_value(t_envp **my_envp, char *str, int idx)
{
	t_envp	*new;

	new = (t_envp *)malloc(sizeof(t_envp));
	if (new == NULL)
		exit(1);
	if (idx == 0)
	{
		new->key = ft_strdup(str);
		new->value = NULL;
	}
	else if (str[idx + 1] == '\0')
	{
		new->key = ft_substr(str, 0, idx);
		new->value = ft_strdup("\0");
	}
	else
	{
		new->key = ft_substr(str, 0, idx);
		new->value = ft_substr(str, idx + 1, ft_strlen(str) - idx - 1);
	}
	new->key_len = ft_strlen(new->key);
	new->value_len = ft_strlen(new->value);
	new->next = NULL;
	envp_add_back(my_envp, new);
}

void	print_envp(t_envp **my_envp)
{
	int		lst_size;
	int		i;
	t_envp	*n;

	i = 0;
	lst_size = envp_size(my_envp);
	n = *my_envp;
	while (i < lst_size)
	{
		if (n->key[0] != '?')
		{
			ft_putstr_fd("declare -x ", 1);
			ft_putstr_fd(n->key, 1);
			if (n->value != NULL)
			{
				ft_putstr_fd("=", 1);
				ft_putstr_fd("\"", 1);
				ft_putstr_fd(n->value, 1);
				ft_putstr_fd("\"", 1);
			}
			ft_putstr_fd("\n", 1);
		}
		i++;
		n = n->next;
	}
}
