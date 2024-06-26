/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_discriminant.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehyupar <sehyupar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 22:05:11 by sehyupar          #+#    #+#             */
/*   Updated: 2024/06/26 14:51:54 by sehyupar         ###   ########.fr       */
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

int	is_quote(t_parsing_ptr *ptr)
{
	if (ptr->eof == FALSE && \
	(*ptr->end == SINGLE_QUOTE || *ptr->end == DOUBLE_QUOTE))
		return (TRUE);
	return (FALSE);
}

void	add_quote(t_input *list, t_parsing_ptr *ptr, t_quote_flag *flag)
{
	if (*ptr->end == DOUBLE_QUOTE && flag->s_quote == FALSE)
		change_stat(&flag->d_quote);
	else if (*ptr->end == SINGLE_QUOTE && flag->d_quote == FALSE)
		change_stat(&flag->s_quote);
	while ((flag->s_quote == TRUE || flag->d_quote == TRUE))
	{
		move_end(ptr);
		if (ptr->eof == TRUE)
		{
			list->valid = FALSE;
			ft_putstr_fd("minishell: unclosed quotes\n", 2);
			break ;
		}
		if (*ptr->end == DOUBLE_QUOTE && flag->s_quote == FALSE)
			change_stat(&flag->d_quote);
		else if (*ptr->end == SINGLE_QUOTE && flag->d_quote == FALSE)
			change_stat(&flag->s_quote);
	}
}
