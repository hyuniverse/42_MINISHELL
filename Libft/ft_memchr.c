/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siychoi <siychoi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 15:33:27 by siychoi           #+#    #+#             */
/*   Updated: 2023/11/03 11:43:50 by siychoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*mem;
	unsigned char	chr;

	chr = (unsigned char)c;
	mem = (unsigned char *)s;
	i = 0;
	while (i < n)
	{
		if (mem[i] == chr)
			return ((void *)(s + i));
		i++;
	}
	return ((void *)0);
}
