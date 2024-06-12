/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_discriminant.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehyupar <sehyupar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 22:05:11 by sehyupar          #+#    #+#             */
/*   Updated: 2024/06/12 20:08:37 by sehyupar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_space(char ch)
{
	if ((ch >= 9 && ch <= 13) || ch == 32)
		return (TRUE);
	return (FALSE);
}

int	is_pipe(t_input *list, char *str, char start)
{
	int	i;

	i = 0;
	if (!str)
		exit(1);
	while (str[i] && is_space(str[i]))
		i++;
	if ((start == '|' && list->head->cnt == 0) || !str[i] || str[i] == '|')
	{
		if (!str[i])
			print_syntax_error("");
		else
			print_syntax_error("|");
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

void	add_quote(t_parsing_ptr *ptr, t_quote_flag *flag)
{
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
}

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

void	add_redirection(t_input *list, t_parsing_ptr *ptr)
{
	char	rd;
	int		type;

	rd = *ptr->end;
	if (ptr->len != 0)
		add_token_back(list->tail, ptr);
	while (ptr->eof == FALSE && ptr->len < 2 && *ptr->end == rd)
		move_end(ptr);
	type = get_rd_type(rd, ptr->len);
	while (ptr->eof == FALSE && is_space(*ptr->end))
		move_end(ptr);
	set_start(ptr);
	while (ptr->eof == FALSE && !is_discriminant(*ptr->end))
		move_end(ptr);
	if (ptr->len > 0)
		add_token_rd(list->tail, ptr, type);
	else
	{
		print_syntax_error(ptr->end);
		list->valid = FALSE;
	}
}
