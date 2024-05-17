/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_essentials.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehyupar <sehyupar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 15:44:50 by sehyupar          #+#    #+#             */
/*   Updated: 2024/05/17 16:21:12 by sehyupar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_lexing_flag(t_lexing_flag *flag)
{
	flag->cmd = FALSE;
	flag->s_quote = FALSE;
	flag->d_quote = FALSE;
}

t_input	*initial_process(char *str, t_lexing_flag *flag, t_parsing_ptr *ptr)
{
	t_input	*list;

	init_lexing_flag(flag);
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
	else if (list->head->cnt == 0) // 사용 안한  heredoc phrase 삭제
		delete_front(list);
	//printf("final process completed");
	return (list);
}
