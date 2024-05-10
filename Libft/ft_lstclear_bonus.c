/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siychoi <siychoi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 11:33:50 by siychoi           #+#    #+#             */
/*   Updated: 2023/11/04 18:46:31 by siychoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*now_node;
	t_list	*next_node;

	if (lst == NULL)
		return ;
	next_node = *lst;
	while (*lst != NULL)
	{
		now_node = (*lst)->next;
		ft_lstdelone(*lst, del);
		(*lst) = now_node;
	}
	(*lst) = 0;
}
