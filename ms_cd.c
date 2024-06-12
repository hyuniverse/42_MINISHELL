/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siychoi <siychoi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 15:35:28 by siychoi           #+#    #+#             */
/*   Updated: 2024/06/10 14:19:19 by siychoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	print_cd_error(char *str, int error_type);
static int	ms_cd_no_options(t_envp **my_envp, char *old_pwd);

int	ms_cd(t_envp **my_envp, char **argv)
{
	int		status;
	char	*pwd;

	status = 0;
	pwd = getcwd(NULL, 0);
	if (argv[1] == NULL)
		return (ms_cd_no_options(my_envp, pwd));
	if (argv[1][0] == '-' && argv[1][1] != '\0')
		return (print_cd_error(NULL, 1));
	if (chdir(argv[1]) == -1)
	{
		print_code_error_builtin(errno, argv[0]);
		status = 1;
	}
	else
	{
		change_value(my_envp, "OLDPWD", pwd);
		change_value(my_envp, "PWD", getcwd(NULL, 0));
	}
	return (status);
}

static int	ms_cd_no_options(t_envp **my_envp, char *old_pwd)
{
	if (chdir(find_value(my_envp, "HOME")) == -1)
	{
		ft_putstr_fd("minishell : cd: HOME not set\n", 2);
		return (1);
	}
	else
	{
		change_value(my_envp, "OLDPWD", old_pwd);
		change_value(my_envp, "PWD", getcwd(NULL, 0));
	}
	return (0);
}

static int	print_cd_error(char *str, int error_type)
{
	if (error_type == 1)
	{
		ft_putstr_fd("minishell: cd: can't have options\n", 2);
	}
	else if (error_type == 2)
	{
		ft_putstr_fd("minishell: cd: ", 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
	}
	return (1);
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
			value = n->value;
			break ;
		}
		i++;
		n = n->next;
	}
	return (value);
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
