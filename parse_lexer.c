/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_lexer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siychoi <siychoi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 18:26:47 by sehyupar          #+#    #+#             */
/*   Updated: 2024/05/25 16:05:45 by siychoi          ###   ########.fr       */
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
		else if (ptr.eof == FALSE)
			move_end(&ptr);
	}
	return (final_process(list));
}
