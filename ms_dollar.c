/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_dollar.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siychoi <siychoi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 16:55:33 by siychoi           #+#    #+#             */
/*   Updated: 2024/06/13 17:32:46 by siychoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	change_dollar_value(t_envp **my_envp, t_phrase *phrase, char *s, int *i)
{
	char	*key;
	char	*value;
	int		j;

	j = 1;
	while (s[j])
	{
		if (is_space(s[j]) || ft_isalnum(s[j]) == FALSE)
			break ;
		j++;
	}
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

char	*change_dollar_sign(t_envp **my_envp, t_token *token)
{
	int				i;
	t_quote_flag	flag;
	int				cnt;
	char			*str;
	t_phrase		*phrase;

	i = 0;
	init_quote_flag(&flag);
	phrase = get_phrase();
	if (phrase == NULL)
		exit(1);
	cnt = 0;
	str = token->data;
	while (str && i < (int)ft_strlen(token->data))
	{
		if (str[i] == DOUBLE_QUOTE && flag.s_quote == FALSE)
		{
			if (cnt != 0)
				add_token(phrase, ft_substr(str, i - cnt, cnt), &cnt);
			change_stat(&flag.d_quote);
			i++;
		}
		else if (str[i] == SINGLE_QUOTE && flag.d_quote == FALSE)
		{
			if (cnt != 0)
				add_token(phrase, ft_substr(str, i - cnt, cnt), &cnt);
			change_stat(&flag.s_quote);
			i++;
		}
		else
		{
			if (str[i] == '$' && flag.s_quote == FALSE && str[i + 1] != '"' && str[i + 1] != '\0')
			{
				if (cnt != 0)
					add_token(phrase, ft_substr(str, i - cnt, cnt), &cnt);
				if (change_dollar_value(my_envp, phrase, &str[i], &i))
					cnt = 0;
			}
			else
			{
				i++;
				cnt++;
			}
		}
	}
	if (cnt != 0)
		add_token(phrase, ft_substr(str, i - cnt, cnt), &cnt);
	return (phrase_to_str(phrase));
}

void	change_dollar_all_tokens(t_input *input, t_envp **my_envp)
{
	t_phrase	*phrase;
	t_token		*token;
	char		*tmp;

	phrase = input->head;
	while (phrase)
	{
		token = phrase->head;
		while (token)
		{
			tmp = change_dollar_sign(my_envp, token);
			free(token->data);
			token->data = tmp;
			token = token->next;
		}
		phrase = phrase->next;
	}	
}
