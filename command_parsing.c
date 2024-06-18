/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_parsing.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siychoi <siychoi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 13:05:48 by siychoi           #+#    #+#             */
/*   Updated: 2024/06/17 18:47:06 by siychoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*cmd_strjoin(char const *s1, char const *s2, char *s3)
{
	char	*temp;
	int		i;
	int		s1_len;
	int		s2_len;
	int		s3_len;

	i = 0;
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	s3_len = ft_strlen(s3);
	temp = (char *)malloc(sizeof(char) * (s1_len + s2_len + s3_len + 1));
	if (!temp)
		return (NULL);
	ft_strlcpy(temp, s1, s1_len + 1);
	ft_strlcat(temp + s1_len, s2, s2_len + 1);
	ft_strlcat(temp + s1_len + s2_len, s3, s3_len + 1);
	return (temp);
}

char	*find_path(char **env)
{
	char	*path;

	path = NULL;
	while (*env)
	{
		if (ft_strnstr(*env, "PATH=", 5) != NULL)
		{
			path = ft_strnstr(*env, "PATH=", 5) + 5;
			break ;
		}
		env++;
	}
	return (path);
}

int	count_backslash(char *str)
{
	int	i;
	int	cnt;

	i = 0;
	cnt = 0;
	while (str[i])
	{
		if (str[i] == '\\')
		{
			cnt++;
			i++;
		}
		if (str[i] != '\0')
			i++;
	}
	return (cnt);
}

char	*remove_backslash(char *str)
{
	char	*temp;
	int		temp_idx;
	int		cnt;
	int		i;

	temp_idx = 0;
	cnt = count_backslash(str);
	i = 0;
	temp = (char *)malloc(sizeof(char) * (ft_strlen(str) - cnt + 1));
	if (temp == NULL)
		return (NULL);
	while (str[i])
	{
		if (str[i] == '\\' && str[i + 1] != '\0')
			i++;
		temp[temp_idx] = str[i];
		i++;
		temp_idx++;
	}
	temp[ft_strlen(str) - cnt] = '\0';
	free(str);
	return (temp);
}
