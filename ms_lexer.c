/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_lexer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehyupar <sehyupar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 18:26:47 by sehyupar          #+#    #+#             */
/*   Updated: 2024/05/10 20:47:00 by sehyupar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	change_stat(int *flag)
{
	if (*flag == TRUE)
		*flag = FALSE;
	else if (*flag == FALSE)
		*flag = TRUE;
}

void	quote(t_parsing_ptr *ptr, t_lexing_flag *flag)
{
	printf("!!!!!!!!!!!!!quote process\n");
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
	}
	printf("!!!!!!!!!!!!!quote process completed\n");
	move_end(ptr);
}

void	init_lexing_flag(t_lexing_flag *flag)
{
	flag->cmd = FALSE;
	flag->s_quote = FALSE;
	flag->d_quote = FALSE;
}

void	add_redirection(t_phrase *phrase, t_parsing_ptr *ptr)
{
	char	rd;

	rd = *ptr->end;
	if (ptr->len != 0)
		add_token_back(phrase, ptr);
	while (ptr->eof == FALSE && ptr->len < 2 && *ptr->end == rd)
		move_end(ptr);
	while (ptr->eof == FALSE && is_space(*ptr->end))
		move_end(ptr);
	while (ptr->eof == FALSE && !is_space(*ptr->end) \
	&& *ptr->end != '|' && *ptr->end != '>' && *ptr->end != '<')
		move_end(ptr);
	add_token_front(phrase, ptr);
}

t_input	*lexer(char *str)
{
	t_input			*list;
	t_lexing_flag	flag;
	t_parsing_ptr	ptr;

	init_lexing_flag(&flag);
	init_ptr(&ptr, str);
	list = get_input(&ptr);
	while (TRUE)
	{
		if (ptr.eof == TRUE)
		{
			if (ptr.len != 0)
				add_token_back(list->tail, &ptr);
			break;
		}
		if (is_space(*ptr.end) == TRUE)
		{
			printf("is space > ");
			if (ptr.len != 0)
				add_token_back(list->tail, &ptr);
			while (is_space(*ptr.end) == TRUE)
				move_start(&ptr);
		}
		if (*ptr.end == SINGLE_QUOTE || *ptr.end == DOUBLE_QUOTE)
		{
			printf("is quote > ");
			quote(&ptr, &flag);
		}
		if ((*ptr.end == '<' || *ptr.end == '>'))//&& is_redirection(&ptr)
		{
			printf("is redirection > ");
			add_redirection(list->tail, &ptr);
		}
		else if (*ptr.end == '|')// && is_pipe(&ptr)
		{
			printf("is phrase > ");
			add_phrase(list, &ptr);
		}
		else
			move_end(&ptr);
	}
	return (list);
}
