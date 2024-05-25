/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_builtin_cmd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siychoi <siychoi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 16:24:25 by siychoi           #+#    #+#             */
/*   Updated: 2024/05/25 16:05:41 by siychoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exe_only_builtin_cmd(t_envp **my_envp, t_phrase *phrase)
{
	char	**s_cmd;

	s_cmd = token_to_arr(phrase);
	if (ms_strncmp(s_cmd[0], "cd", ft_strlen(phrase->head->data)) == 0)
		return (ms_cd(my_envp, s_cmd));
	else if (ms_strncmp(s_cmd[0], "echo", ft_strlen(phrase->head->data)) == 0)
		return (ms_echo(s_cmd));
	else if (ms_strncmp(s_cmd[0], "env", ft_strlen(phrase->head->data)) == 0)
		return (ms_env(my_envp, s_cmd));
	else if (ms_strncmp(s_cmd[0], "exit", ft_strlen(phrase->head->data)) == 0)
		return (ms_exit(s_cmd));
	else if (ms_strncmp(s_cmd[0], "export", ft_strlen(phrase->head->data)) == 0)
		return (ms_export(my_envp, s_cmd));
	else if (ms_strncmp(s_cmd[0], "pwd", ft_strlen(phrase->head->data)) == 0)
		return (ms_pwd(s_cmd));
	else if (ms_strncmp(s_cmd[0], "unset", ft_strlen(phrase->head->data)) == 0)
		return (ms_unset(my_envp, s_cmd));
	else
		return (0);
}

int	exe_child_builtin_cmd(t_envp **my_envp, t_phrase *phrase)
{
	char	**s_cmd;

	s_cmd = token_to_arr(phrase);
	if (ms_strncmp(s_cmd[0], "cd", ft_strlen(phrase->head->data)) == 0)
		exit(ms_cd(my_envp, s_cmd));
	else if (ms_strncmp(s_cmd[0], "echo", ft_strlen(phrase->head->data)) == 0)
		exit(ms_echo(s_cmd));
	else if (ms_strncmp(s_cmd[0], "env", ft_strlen(phrase->head->data)) == 0)
		exit(ms_env(my_envp, s_cmd));
	else if (ms_strncmp(s_cmd[0], "exit", ft_strlen(phrase->head->data)) == 0)
		exit(ms_exit(s_cmd));
	else if (ms_strncmp(s_cmd[0], "export", ft_strlen(phrase->head->data)) == 0)
		exit(ms_export(my_envp, s_cmd));
	else if (ms_strncmp(s_cmd[0], "pwd", ft_strlen(phrase->head->data)) == 0)
		exit(ms_pwd(s_cmd));
	else if (ms_strncmp(s_cmd[0], "unset", ft_strlen(phrase->head->data)) == 0)
		exit(ms_unset(my_envp, s_cmd));
	else
		exit(0);
	return (0);
}

int	is_builtin_cmd(t_phrase *phrase)
{
	if (ms_strncmp(phrase->head->data, "cd", 2) == 0
	|| ms_strncmp(phrase->head->data, "echo", 4) == 0
	|| ms_strncmp(phrase->head->data, "env", 3) == 0
	|| ms_strncmp(phrase->head->data, "exit", 4) == 0
	|| ms_strncmp(phrase->head->data, "export", 6) == 0
	|| ms_strncmp(phrase->head->data, "pwd", 3) == 0
	|| ms_strncmp(phrase->head->data, "unset", 5) == 0)
		return (TRUE);
	else
		return (FALSE);
}

//int	check_builtin_cmd(t_envp **my_envp, t_phrase *phrase)
//{
//	char	**s_cmd;
//	char	**envp;
	
//	s_cmd = token_to_arr(phrase);
//	if (ms_strncmp(s_cmd[0], "cd", ft_strlen(phrase->head->data)) == 0)
//		return (ms_cd(my_envp, s_cmd));
//	else if (ms_strncmp(s_cmd[0], "echo", ft_strlen(phrase->head->data)) == 0)
//		return (ms_echo(s_cmd));
//	else if (ms_strncmp(s_cmd[0], "env", ft_strlen(phrase->head->data)) == 0)
//		return (ms_env(my_envp, s_cmd));
//	else if (ms_strncmp(s_cmd[0], "exit", ft_strlen(phrase->head->data)) == 0)
//		return (ms_exit(s_cmd));
//	else if (ms_strncmp(s_cmd[0], "export", ft_strlen(phrase->head->data)) == 0)
//		return (ms_export(my_envp, s_cmd));
//	else if (ms_strncmp(s_cmd[0], "pwd", ft_strlen(phrase->head->data)) == 0)
//		return (ms_pwd(s_cmd));
//	else if (ms_strncmp(s_cmd[0], "unset", ft_strlen(phrase->head->data)) == 0)
//		return (ms_unset(my_envp, s_cmd));
//	else
//		return (builtout_cmd(phrase, envp));
//}
