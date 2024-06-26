/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_add_redirection.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehyupar <sehyupar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 14:40:53 by sehyupar          #+#    #+#             */
/*   Updated: 2024/06/26 14:55:08 by sehyupar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_rd_type(char ch, int len)
{
	if (ch == '<' && len == 1)
		return (IN);
	else if (ch == '<' && len == 2)
		return (HD);
	else if (ch == '>' && len == 1)
		return (OUT);
	else if (ch == '>' && len == 2)
		return (APD);
	else
		return (-1);
}

void	get_redirection_token(t_input *list, t_parsing_ptr *ptr)
{
	t_quote_flag	flag;

	init_quote_flag(&flag);
	while (ptr->eof == FALSE && !is_discriminant(*ptr->end))
	{
		if (is_quote(ptr))
		{
			add_quote(list, ptr, &flag);
			move_end(ptr);
		}
		else
			move_end(ptr);
	}
}

void	add_redirection(t_input *list, t_parsing_ptr *ptr)
{
	char			rd;
	int				type;

	rd = *ptr->end;
	if (ptr->len != 0)
		add_token_back(list->tail, ptr);
	while (ptr->eof == FALSE && ptr->len < 2 && *ptr->end == rd)
		move_end(ptr);
	type = get_rd_type(rd, ptr->len);
	while (ptr->eof == FALSE && is_space(*ptr->end))
		move_end(ptr);
	set_start(ptr);
	get_redirection_token(list, ptr);
	if (ptr->len > 0)
		add_token_rd(list->tail, ptr, type);
	else
	{
		print_syntax_error(ptr->end);
		list->valid = FALSE;
	}
}
