/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehyupar <sehyupar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 22:07:28 by siychoi           #+#    #+#             */
/*   Updated: 2024/06/27 14:57:38 by sehyupar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_2d_array(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
		free(arr[i++]);
	free(arr);
}

int	ms_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		if (s1[i] != s2[i] || s1[i] == '\0' || s2[i] == '\0')
			return ((unsigned char)(s1[i]) - (unsigned char)(s2[i]));
		i++;
	}
	if (ft_strlen(s1) == ft_strlen(s2))
		return (0);
	return (1);
}

int	count_token_data(t_token *token, int *cnt)
{
	int	i;

	i = 0;
	while (token != NULL)
	{
		if (*token->data)
		{
			(*cnt)++;
			i++;
		}
		token = token->next;
	}
	return (i);
}

char	**token_to_arr(t_phrase *phrase)
{
	char	**result;
	int		i;
	int		cnt;
	t_token	*token;

	i = 0;
	cnt = 0;
	token = phrase->head;
	if (count_token_data(token, &cnt) == 0)
		exit(0);
	result = (char **)malloc(sizeof(char *) * (cnt + 1));
	if (result == NULL)
		exit(1);
	token = phrase->head;
	while (i < cnt)
	{
		if (*token->data)
		{
			result[i] = ft_strdup(token->data);
			i++;
		}
		token = token->next;
	}
	result[i] = NULL;
	return (result);
}
