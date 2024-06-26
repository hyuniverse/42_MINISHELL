/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_lexer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehyupar <sehyupar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 18:26:47 by sehyupar          #+#    #+#             */
/*   Updated: 2024/06/26 14:51:40 by sehyupar         ###   ########.fr       */
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
	t_quote_flag	flag;
	t_parsing_ptr	ptr;

	list = initial_process(str, &flag, &ptr);
	while (list->valid == TRUE)
	{
		if ((ptr.eof == TRUE || is_space(*ptr.end) == TRUE) && ptr.len != 0)
			add_token_back(list->tail, &ptr);
		while (ptr.eof == FALSE && is_space(*ptr.end) == TRUE)
			move_start(&ptr);
		if (ptr.eof == TRUE)
			break ;
		if (is_quote(&ptr))
			add_quote(list, &ptr, &flag);
		if (ptr.eof == FALSE && (*ptr.end == '<' || *ptr.end == '>'))
			add_redirection(list, &ptr);
		else if (ptr.eof == FALSE && *ptr.end == '|' && \
		is_pipe(list, ptr.end + 1, *ptr.start))
			add_phrase(list, &ptr);
		else if (ptr.eof == FALSE)
			move_end(&ptr);
	}
	return (final_process(list));
}
