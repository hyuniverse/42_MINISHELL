/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_lexer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehyupar <sehyupar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 18:26:47 by sehyupar          #+#    #+#             */
/*   Updated: 2024/05/16 18:11:38 by sehyupar         ###   ########.fr       */
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

t_input	*lexer(char *str)
{
	t_input			*list;
	t_lexing_flag	flag;
	t_parsing_ptr	ptr;

	list = initial_process(str, &flag, &ptr);
	while (list->valid == TRUE)
	{
		if ((ptr.eof == TRUE || is_space(*ptr.end) == TRUE) && ptr.len != 0)
			add_token_back(list->tail, &ptr);
		while (ptr.eof == FALSE && is_space(*ptr.end) == TRUE)
			move_start(&ptr);
		if (ptr.eof == FALSE && (*ptr.end == SINGLE_QUOTE || *ptr.end == DOUBLE_QUOTE))
			add_quote(&ptr, &flag);
		if (ptr.eof == TRUE)
			break ;
		if ((*ptr.end == '<' || *ptr.end == '>'))
			add_redirection(list, &ptr);
		else if (*ptr.end == '|' && is_pipe(list, ptr.end + 1))
			add_phrase(list, &ptr);
		/*
		else if (*ptr.end == '$' && *(ptr.end + 1) && !is_space(*(ptr.end + 1)))
			sub_env();
		*/
		else if (ptr.eof == FALSE)
			move_end(&ptr);
	}
	return (final_process(list));
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
