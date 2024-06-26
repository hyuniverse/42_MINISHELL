/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_dollar.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehyupar <sehyupar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 16:55:33 by siychoi           #+#    #+#             */
/*   Updated: 2024/06/26 16:32:12 by sehyupar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*change_dollar_sign(t_envp **my_envp, t_token *token)
{
	t_quote_flag	flag;
	t_phrase		*phrase;
	t_expansion		e;

	init_quote_flag(&flag);
	init_expansion_var(&e, token);
	phrase = get_phrase();
	if (phrase == NULL)
		exit(1);
	while (e.str && e.i < (int)ft_strlen(token->data))
	{
		if (e.str[e.i] == DOUBLE_QUOTE && flag.s_quote == FALSE)
			quote_process(phrase, &e, &flag.d_quote);
		else if (e.str[e.i] == SINGLE_QUOTE && flag.d_quote == FALSE)
			quote_process(phrase, &e, &flag.s_quote);
		else
			expansion_proc(my_envp, phrase, &e, flag.s_quote);
	}
	if (e.cnt != 0)
		add_token(phrase, ft_substr(e.str, e.i - e.cnt, e.cnt), &e.cnt);
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
