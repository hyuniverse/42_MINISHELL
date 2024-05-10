/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_methods_input.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehyupar <sehyupar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 16:57:28 by sehyupar          #+#    #+#             */
/*   Updated: 2024/05/10 20:34:43 by sehyupar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_input	*get_input(t_parsing_ptr *ptr)
{
	t_input	*list;

	list = (t_input *)malloc(sizeof(t_input));
	if (!list)
		return (0);
	add_phrase(list, ptr);
	//add_phrase(list);
	return (list);
}

void	free_token(t_token *token)
{
	printf("free: %s\n", token->data);
	if (token->next)
		free_token(token->next);
	free(token->data);
	free(token);
}

void	free_phrase(t_phrase *phrase)
{
	free_token(phrase->head);
	if (phrase->next)
		free_phrase(phrase->next);
	free(phrase);
}

void	free_input(t_input *list)
{
	free_phrase(list->head);
	free(list);
}
