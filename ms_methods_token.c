/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_methods_token.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehyupar <sehyupar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 15:01:55 by sehyupar          #+#    #+#             */
/*   Updated: 2024/05/10 18:28:28 by sehyupar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*my_strldup(t_parsing_ptr *ptr)
{
	char	*dup;
	int		i;
	int		len;

	len = ptr->len;
	i = 0;
	if (len == 0)
		return (0);
	dup = (char *)malloc(len + 1);
	if (!dup)
		return (0);
	while (i < len)
	{
		dup[i] = (ptr->start)[i];
		i++;
	}
	dup[i] = 0;
	return (dup);
}

t_token	*get_token(int type, t_parsing_ptr *ptr)
{
	t_token	*token;

	token = (t_token *)malloc(sizeof(t_token));
	if (!token)
		return (0);
	token->data = my_strldup(ptr);
	printf("token: %s\n", token->data);
	token->next = 0;
	token->type = type;
	//ptr->end++;
	set_start(ptr);
	return (token);
}

void	add_token_back(t_phrase *phrase, t_parsing_ptr *ptr)
{
	t_token	*token;

	token = get_token(CNT, ptr);
	if (!token)
		return ;
	if (!phrase->tail)
		phrase->head = token;
	else
		phrase->tail->next = token;
	phrase->tail = token;
	phrase->cnt++;
}

void	add_token_front(t_phrase *phrase, t_parsing_ptr *ptr)
{
	t_token	*token;

	token = get_token(RD, ptr);
	if (!token)
		return ;
	if (!phrase->head)
		phrase->tail = token;
	else
		token->next = phrase->head;
	phrase->head = token;
	phrase->cnt++;
}