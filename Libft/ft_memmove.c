/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siychoi <siychoi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 10:47:10 by siychoi           #+#    #+#             */
/*   Updated: 2023/11/03 12:53:34 by siychoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t			i;
	unsigned char	*mem1;
	unsigned char	*mem2;

	mem1 = (unsigned char *)dst;
	mem2 = (unsigned char *)src;
	if (mem1 == NULL && mem2 == NULL)
		return (NULL);
	i = -1;
	if (mem1 > mem2)
	{
		while (++i < len)
			mem1[len - 1 - i] = mem2[len - 1 - i];
	}
	else
	{
		while (++i < len)
			mem1[i] = mem2[i];
	}
	return (dst);
}
