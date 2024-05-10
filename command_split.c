/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_split.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siychoi <siychoi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 13:03:19 by siychoi           #+#    #+#             */
/*   Updated: 2024/05/09 19:12:00 by siychoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	move_i_to_end(char const *s, int *i)
{
	if (s[*i] != '\0')
		(*i)++;
}

int	cmd_split_count(char const *s, int i, int cnt)
{
	while (s[i])
	{
		if (s[i] != ' ' && s[i] != '\'' && s[i] != '\"')
		{
			cnt++;
			while (s[i] != ' ' && s[i])
				i++;
		}
		else if (s[i] == '\'')
		{
			cnt++;
			i++;
			while (s[i] && s[i] != '\'')
				i++;
		}
		else if (s[i] == '\"')
		{
			cnt++;
			i++;
			while (s[i] && s[i] != '\"')
				i++;
		}
		move_i_to_end(s, &i);
	}
	return (cnt);
}

static void	make_result2(char *str, char **result, int i, int idx)
{
	*result = (char *)malloc(sizeof(char) * (i - idx) + 1);
	if (*result == NULL)
	{
		ft_putendl_fd("Error", 2);
		exit(1);
	}
	ft_strlcpy(*result, str + idx, i - idx + 1);
}

static void	make_result(char *s, char **result, int i, int idx)
{
	while (s[i])
	{
		if (s[i] != ' ' && s[i] != '\'' && s[i] != '\"')
		{
			idx = i;
			while (s[i] != ' ' && s[i])
				i++;
			make_result2(s, result++, i, idx);
		}
		else if (s[i] == '\'')
		{
			idx = ++i;
			while ((s[i] != '\'' && s[i]) || (s[i - 1] == 92 && s[i] == '\''))
				i++;
			make_result2(s, result++, i, idx);
		}
		else if (s[i] == '\"')
		{
			idx = ++i;
			while ((s[i] != '\"' && s[i]) || (s[i - 1] == 92 && s[i] == '\"'))
				i++;
			make_result2(s, result++, i, idx);
		}
		move_i_to_end(s, &i);
	}
}

char	**cmd_split(char *str)
{
	char	**result;
	int		i;
	int		arr_cnt;

	i = 0;
	arr_cnt = cmd_split_count(str, 0, 0);
	result = (char **)malloc(sizeof(char *) * (arr_cnt + 1));
	if (result == NULL)
	{
		ft_putendl_fd("Error", 2);
		exit(1);
	}
	make_result(str, result, 0, 0);
	result[arr_cnt] = NULL;
	while (result[i])
	{
		result[i] = remove_backslash(result[i]);
		i++;
	}
	return (result);
}
