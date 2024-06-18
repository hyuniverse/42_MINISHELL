/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siychoi <siychoi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 09:22:21 by siychoi           #+#    #+#             */
/*   Updated: 2024/06/17 18:53:59 by siychoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	split_count(char const *s, char c)
{
	int	i;
	int	cnt;

	i = 0;
	cnt = 0;
	if (s == NULL)
		return (0);
	while (s[i])
	{
		if (s[i] != c)
		{
			cnt++;
			while (s[i] != c && s[i])
				i++;
		}
		if (s[i] != '\0')
			i++;
	}
	return (cnt);
}

int	make_result2(char const *s, char **result, int i, int j)
{
	*result = (char *)malloc(sizeof(char) * (i - j) + 1);
	if (*result == NULL)
		return (1);
	ft_strlcpy(*result, s + j, i - j + 1);
	return (0);
}

int	make_result(char const *s, char c, char **result, int flag)
{
	int	i;
	int	j;
	int	cnt;

	i = -1;
	cnt = 0;
	while (s[++i])
	{
		if (s[i] != c && flag == 0)
		{
			j = i;
			flag = 1;
			cnt++;
		}
		else if (s[i] == c && flag == 1)
		{
			if (make_result2(s, result++, i, j) != 0)
				return (cnt);
			flag = 0;
		}
	}
	if (flag == 1)
		if (make_result2(s, result, i, j) != 0)
			return (cnt);
	return (0);
}

char	**ft_split(char const *s, char c)
{
	char	**result;
	int		arr_cnt;
	int		idx;
	int		cnt;

	idx = -1;
	arr_cnt = split_count(s, c);
	result = (char **)malloc(sizeof(char *) * (arr_cnt + 1));
	if (result == NULL)
		return (NULL);
	if (s == NULL)
	{
		result[0] = NULL;
		return (result);
	}
	cnt = make_result(s, c, result, 0);
	if (cnt > 0)
	{
		while (--cnt > 0)
			free(result[++idx]);
		free(result);
		return (NULL);
	}
	result[arr_cnt] = 0;
	return (result);
}
