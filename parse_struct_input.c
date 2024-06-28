/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_struct_input.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siychoi <siychoi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 16:57:28 by sehyupar          #+#    #+#             */
/*   Updated: 2024/06/28 22:16:14 by siychoi          ###   ########.fr       */
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
	if (token->next)
		free_token(token->next);
	free(token->data);
	free(token);
}

void	free_phrase(t_phrase *phrase)
{	
	if (phrase->head)
	{
		if (phrase->infile_name != NULL && phrase->infile_type != 6)
			free(phrase->infile_name);
		if (phrase->outfile_name != NULL)
			free(phrase->outfile_name);
		free_token(phrase->head);
	}
	if (phrase->next)
		free_phrase(phrase->next);
	free(phrase);
}

void	free_input(t_input *list)
{
	if (!list)
		return ;
	if (list->head)
		free_phrase(list->head);
	free(list);
}
