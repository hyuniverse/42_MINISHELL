/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_pointer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehyupar <sehyupar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 20:51:01 by sehyupar          #+#    #+#             */
/*   Updated: 2024/05/21 16:40:00 by sehyupar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_ptr(t_parsing_ptr *ptr, char *str)
{
	ptr->start = str;
	ptr->end = str;
	//printf("start> %s\n", ptr->start);
	ptr->len = 0;
	//ptr->sub = 0;
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
/*
	else
		printf("####set start(' %c ')####\n", *ptr->start);
*/

}

void	move_start(t_parsing_ptr *ptr)
{
	ptr->start++;
	ptr->end++;
	if (!*ptr->end)
		ptr->eof = TRUE;
/*
	else
		printf("####move start(' %c(%d) ')####\n", *ptr->start, *ptr->start);
*/

}

int	move_end(t_parsing_ptr *ptr)
{
	ptr->end++;
	ptr->len++;
	if (!*ptr->end)
		ptr->eof = TRUE;
/*
	else
		printf("####move end(' %c ')####\n", *ptr->end);
*/

	return (1);
}
