/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_struct_phrase.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehyupar <sehyupar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 16:57:30 by sehyupar          #+#    #+#             */
/*   Updated: 2024/05/16 15:22:12 by sehyupar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_phrase	*get_phrase(void)
{
	t_phrase	*phrase;

	phrase = (t_phrase *)malloc(sizeof(t_phrase));
	if (!phrase)
		return (0);
	phrase->head = 0;
	phrase->tail = 0;
	phrase->rd = 0;
	phrase->next = 0;
	phrase->type = 0;
	phrase->cnt = 0;
	return (phrase);
}

void	add_phrase(t_input *list, t_parsing_ptr *ptr)
{
	t_phrase	*phrase;

	if (ptr->len != 0)
		add_token_back(list->tail, ptr);
	phrase = get_phrase();
	if (list->cnt == 0)
	{
		list->head = phrase;
		phrase->type = HD;
	}
	else
	{
		list->tail->next = phrase;
		phrase->type = CNT;
	}
	list->tail = phrase;
	list->cnt++;
	if (list->cnt > 2)
	{
		move_end(ptr);
		set_start(ptr);
	}
}

void	delete_front(t_input *list)
{
	t_phrase	*phrase;

	phrase = list->head;
	list->head = list->head->next;
	phrase->next = 0;
	phrase->type = 0;
	list->cnt--;
	free(phrase);
}
