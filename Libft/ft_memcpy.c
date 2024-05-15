/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siychoi <siychoi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 10:48:24 by siychoi           #+#    #+#             */
/*   Updated: 2023/11/09 10:45:30 by siychoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*mem1;
	unsigned char	*mem2;

	i = 0;
	mem1 = (unsigned char *)dst;
	mem2 = (unsigned char *)src;
	if (mem1 == NULL && mem2 == NULL)
		return (NULL);
	while (i < n)
	{
		mem1[i] = mem2[i];
		i++;
	}
	return (dst);
}
