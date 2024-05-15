/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_discriminant.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehyupar <sehyupar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 22:05:11 by sehyupar          #+#    #+#             */
/*   Updated: 2024/05/15 20:57:17 by sehyupar         ###   ########.fr       */
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
