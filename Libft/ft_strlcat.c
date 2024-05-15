/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siychoi <siychoi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 13:01:48 by siychoi           #+#    #+#             */
/*   Updated: 2024/04/08 21:50:54 by siychoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	len_dst;
	size_t	len_src;
	size_t	idx_dst;
	size_t	idx_src;

	if (dst == NULL && dstsize == 0)
		return (ft_strlen(src));
	len_dst = ft_strlen(dst);
	len_src = ft_strlen(src);
	idx_dst = len_dst;
	idx_src = 0;
	if (len_dst + 1 > dstsize)
		return (len_src + dstsize);
	while (src[idx_src] && (idx_src + len_dst + 1) < dstsize)
	{
		dst[idx_dst] = src[idx_src];
		idx_dst++;
		idx_src++;
	}
	dst[idx_dst] = '\0';
	return (len_src + len_dst);
}
