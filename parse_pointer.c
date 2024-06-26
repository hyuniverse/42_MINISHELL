/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_pointer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehyupar <sehyupar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 20:51:01 by sehyupar          #+#    #+#             */
/*   Updated: 2024/06/26 14:42:56 by sehyupar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_ptr(t_parsing_ptr *ptr, char *str)
{
	ptr->start = str;
	ptr->end = str;
	ptr->len = 0;
	if (str && *str)
		ptr->eof = FALSE;
	else
		ptr->eof = TRUE;
}

void	set_start(t_parsing_ptr *ptr)
{
	ptr->start = ptr->end;
	ptr->len = 0;
	if (!*ptr->end)
		ptr->eof = TRUE;
}

void	move_start(t_parsing_ptr *ptr)
{
	ptr->start++;
	ptr->end++;
	if (!*ptr->end)
		ptr->eof = TRUE;
}

int	move_end(t_parsing_ptr *ptr)
{
	ptr->end++;
	ptr->len++;
	if (!*ptr->end)
		ptr->eof = TRUE;
	return (1);
}
