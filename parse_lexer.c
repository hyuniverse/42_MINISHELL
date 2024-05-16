/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_lexer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehyupar <sehyupar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 18:26:47 by sehyupar          #+#    #+#             */
/*   Updated: 2024/05/16 15:25:07 by sehyupar         ###   ########.fr       */
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
		move_end(ptr);
		cnt++;
	}
	if (cnt > 0)
		add_token_rd(phrase, ptr);
	else
		list->valid = FALSE;
}

t_input	*init(char *str, t_lexing_flag *flag, t_parsing_ptr *ptr)
{
	t_input	*list;

	init_lexing_flag(flag);
	init_ptr(ptr, str);
	list = get_input(ptr);
	return (list);
}

t_input	*final_process(t_input *list)
{
	if (list->valid == FALSE)
	{
		free_input(list);
		perror("!!!!!syntax error near unexpected token");
		list = 0;
	}
	else if (list->head->cnt == 0) // 사용 안한  heredoc phrase 삭제
		delete_front(list);
	printf("final process completed");
	return (list);
}

/*
t_input	*lexer(char *str)
{
	t_input			*list;
	t_lexing_flag	flag;
	t_parsing_ptr	ptr;

	init_lexing_flag(&flag);
	init_ptr(&ptr, str);
	list = get_input(&ptr);
	while (list->valid == TRUE)
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
			add_redirection(list, &ptr);
		}
		else if (*ptr.end == '|')// && is_pipe(&ptr)
		{
			printf("is phrase > ");
			add_phrase(list, &ptr);
		}
		else
			move_end(&ptr);
	}
	printf("out!\n");
	return (final_process(list));
}
*/
t_input	*lexer(char *str)
{
	t_input			*list;
	t_lexing_flag	flag;
	t_parsing_ptr	ptr;

	list = init(str, &flag, &ptr);
	while (list->valid == TRUE)
	{
		if ((ptr.eof == TRUE || is_space(*ptr.end) == TRUE) && ptr.len != 0)
			add_token_back(list->tail, &ptr);
		if (ptr.eof == TRUE)
			break ;
		while (is_space(*ptr.end) == TRUE)
			move_start(&ptr);
		if (*ptr.end == SINGLE_QUOTE || *ptr.end == DOUBLE_QUOTE)
			quote(&ptr, &flag);
		if ((*ptr.end == '<' || *ptr.end == '>'))
			add_redirection(list, &ptr);
		else if (*ptr.end == '|' && is_pipe(list, ptr.end + 1))
			add_phrase(list, &ptr);
		else
			move_end(&ptr);
	}
	return (final_process(list));
}
