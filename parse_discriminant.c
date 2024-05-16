/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_discriminant.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehyupar <sehyupar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 22:05:11 by sehyupar          #+#    #+#             */
/*   Updated: 2024/05/16 16:33:20 by sehyupar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_space(char ch)
{
	if ((ch >= 9 && ch <= 13) || ch == 32)
		return (TRUE);
	return (FALSE);
}

int	is_pipe(t_input *list, char *str)
{
	int			cnt;

	cnt = 0;
	while (*str && is_space(*str))
		str++;
	if (*str && *str == '|')
	{
		list->valid = FALSE;
		return (FALSE);
	}
	return (TRUE);
}

int	is_discriminant(char ch)
{
	if (!is_space(ch) && ch != '|' && ch != '>' && ch != '<')
		return (FALSE);
	return (TRUE);
}

void	add_quote(t_parsing_ptr *ptr, t_lexing_flag *flag)
{
	//printf("!!!!!!!!!!!!!quote process\n");
	if (*ptr->end == DOUBLE_QUOTE && flag->s_quote == FALSE)
		change_stat(&flag->d_quote);
	else if (*ptr->end == SINGLE_QUOTE && flag->d_quote == FALSE)
		change_stat(&flag->s_quote);
	while ((flag->s_quote == TRUE || flag->d_quote == TRUE) \
	&& ptr->eof == FALSE)
	{
		move_end(ptr);
		if (*ptr->end == DOUBLE_QUOTE && flag->s_quote == FALSE)
			change_stat(&flag->d_quote);
		else if (*ptr->end == SINGLE_QUOTE && flag->d_quote == FALSE)
			change_stat(&flag->s_quote);
		/*
		else if (*ptr->end == '$' && flag->d_quote == TRUE)
			sub_env();
		*/
	}
	//printf("!!!!!!!!!!!!!quote process completed\n");
	move_end(ptr);
}

void	add_redirection(t_input *list, t_parsing_ptr *ptr)
{
	char		rd;
	int			cnt;
	t_phrase	*phrase;

	rd = *ptr->end;
	cnt = 0;
	phrase = list->tail;
	if (ptr->len != 0)
		add_token_back(list->tail, ptr);
	while (ptr->eof == FALSE && ptr->len < 2 && *ptr->end == rd)
		move_end(ptr);
	if (rd == '<' && ptr->len == 2)
		phrase = list->head;
	while (ptr->eof == FALSE && is_space(*ptr->end))
		move_end(ptr);
	while (ptr->eof == FALSE && !is_discriminant(*ptr->end))
	{
		cnt += move_end(ptr);
		/*
		if (*ptr->end == '$' && *(ptr->end + 1) && !is_space(*(ptr->end + 1)))
			cnt += sub_env();
		else
			cnt += move_end(ptr);
		*/
	}
	if (cnt > 0)
		add_token_rd(phrase, ptr);
	else
		list->valid = FALSE;
}
