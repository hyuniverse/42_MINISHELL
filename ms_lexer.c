/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_lexer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehyupar <sehyupar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 18:26:47 by sehyupar          #+#    #+#             */
/*   Updated: 2024/05/07 22:33:49 by sehyupar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_space(char ch)
{
	if ((ch >= 9 && ch <= 13) || ch == 32)
		return (TRUE);
	return (FALSE);
}
int	is_command()
{

	return (TRUE);
}

int	is_pipe()
{

	return (TRUE);
}

int	is_redirection()
{

	return (TRUE);
}

void	quote(char **ptr, t_lexing_flag *flag)
{
	char	*endptr;

	endptr = *ptr;
	if (*endptr == DOUBLE_QUOTE && flag->s_quote == FALSE)
		change_stat(&flag->d_quote);
	else if (*endptr == SINGLE_QUOTE && flag->d_quote == FALSE)
		change_stat(&flag->s_quote);
	while ((flag->s_quote == TRUE || flag->d_quote == TRUE) && *(++endptr))
	{
		if (*endptr == DOUBLE_QUOTE && flag->s_quote == FALSE)
			change_stat(&flag->d_quote);
		else if (*endptr == SINGLE_QUOTE && flag->d_quote == FALSE)
			change_stat(&flag->s_quote);	
	}
	*ptr = endptr++;
}

void	change_stat(int *flag)
{
	if (*flag == TRUE)
		*flag == FALSE;
	else if (*flag == FALSE)
		*flag == TRUE;
}

void	add_token()
{

}

void	init_lexing_flag(t_lexing_flag *flag)
{
	flag->cmd = FALSE;
	flag->s_quote = FALSE;
	flag->d_quote = FALSE;
}

t_token	*lexer(char *str)
{
	t_lexing_flag	flag;
	char			*startptr;
	char			*endptr;

	init_lexing_flag(&flag);
	startptr = str;
	endptr = str;
	while (!startptr || !endptr)
	{
		//set starting point
		while (is_space(*startptr))
			startptr++;
		endptr = startptr;
		//qoute checker
		while (endptr && !is_space(*endptr))
		{
			if (*endptr == DOUBLE_QUOTE || *endptr == SINGLE_QUOTE)
				quote(&endptr, &flag);
			//그외 checker
			if (!endptr)
				add_token(&startptr, &endptr, CNT);
			else if ((*endptr == '<' || *endptr == '>') && is_redirection(&endptr))
				add_token(&startptr, &endptr, RD);
			else if (*endptr == '|' && is_pipe(&endptr))
				add_token(&startptr, &endptr, PIPE);
			else if (is_command(&endptr))
				add_token(&startptr, &endptr, CMD);
			else
				endptr++;
		}
	}
}
