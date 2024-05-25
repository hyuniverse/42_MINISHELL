/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_struct_input.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siychoi <siychoi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 16:57:28 by sehyupar          #+#    #+#             */
/*   Updated: 2024/05/25 16:05:46 by siychoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_input	*get_input(t_parsing_ptr *ptr)
{
	t_input	*list;

	list = (t_input *)malloc(sizeof(t_input));
	if (!list)
		return (0);
	list->valid = TRUE;
	list->cnt = 0;
	add_phrase(list, ptr);
	return (list);
}

void	free_token(t_token *token)
{
	//printf("free: %s\n", token->data);
	if (token->next)
		free_token(token->next);
	free(token->data);
	free(token);
}

void	free_phrase(t_phrase *phrase)
{
	//printf("free phrase\n");
	if (phrase->head)
		free_token(phrase->head);
	if (phrase->next)
		free_phrase(phrase->next);
	free(phrase);
}

void	free_input(t_input *list)
{
	//printf("free input\n");
	if (list->head)
		free_phrase(list->head);
	free(list);
}
