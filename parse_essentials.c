/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_essentials.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siychoi <siychoi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 15:44:50 by sehyupar          #+#    #+#             */
/*   Updated: 2024/06/07 16:24:29 by siychoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_quote_flag(t_quote_flag *flag)
{
	flag->s_quote = FALSE;
	flag->d_quote = FALSE;
}

t_input	*initial_process(char *str, t_quote_flag *flag, t_parsing_ptr *ptr)
{
	t_input	*list;

	init_quote_flag(flag);
	init_ptr(ptr, str);
	list = get_input(ptr);
	return (list);
}


t_input	*final_process(t_input *list)
{
	if (list->valid == FALSE)
	{
		free_input(list);
		perror("!!!!!syntax error near unexpected token");
		list = 0;
	}
	//printf("final process completed");
	return (list);
}
