/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_dollar_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehyupar <sehyupar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 16:27:29 by sehyupar          #+#    #+#             */
/*   Updated: 2024/06/26 16:34:36 by sehyupar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	change_dollar_value(t_envp **my_envp, t_phrase *phrase, char *s, int *i)
{
	char	*key;
	char	*value;
	int		j;

	j = 0;
	while (s[++j])
		if (is_space(s[j]) || ft_isalnum(s[j]) == FALSE)
			break ;
	if (s[j] == '?')
		j++;
	*i += j;
	if (j != 1)
	{
		key = ft_substr(s, 1, j - 1);
		value = find_value(my_envp, key);
		if (value)
		{
			j = ft_strlen(value);
			add_token(phrase, value, &j);
		}
		free(key);
		return (1);
	}
	return (0);
}

char	*phrase_to_str(t_phrase *phrase)
{
	char	*str;
	int		i;
	t_token	*token;

	i = 0;
	str = (char *)ft_calloc(phrase->total_len + 1, 1);
	if (str == NULL)
		exit(1);
	token = phrase->head;
	while (i < phrase->cnt)
	{
		ft_strlcat(str, token->data, phrase->total_len + 1);
		token = token->next;
		i++;
	}
	return (str);
}

void	expansion_proc(t_envp **envp, t_phrase *phr, t_expansion *e, int flag)
{
	if (e->str[e->i] == '$' && flag == FALSE && \
	e->str[e->i + 1] != '"' && e->str[e->i + 1] != '\0')
	{
		if (e->cnt != 0)
			add_token(phr, ft_substr(e->str, e->i - e->cnt, e->cnt), &e->cnt);
		if (change_dollar_value(envp, phr, &e->str[e->i], &e->i))
			e->cnt = 0;
		else
			e->cnt ++;
	}
	else
	{
		e->i++;
		e->cnt++;
	}
}

void	quote_process(t_phrase *phrase, t_expansion *e, int *flag)
{
	if (e->cnt != 0)
		add_token(phrase, ft_substr(e->str, e->i - e->cnt, e->cnt), &e->cnt);
	change_stat(flag);
	e->i++;
}

void	init_expansion_var(t_expansion *exp, t_token *token)
{
	exp->i = 0;
	exp->cnt = 0;
	exp->str = token->data;
}
