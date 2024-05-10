/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siychoi <siychoi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 15:17:02 by siychoi           #+#    #+#             */
/*   Updated: 2023/11/03 16:50:48 by siychoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*add;
	char	find;
	int		i;

	i = ft_strlen(s);
	add = (char *)s;
	find = (char)c;
	while (i > 0)
	{
		if (add[i] == find)
			return (add + i);
		i--;
	}
	if (add[i] == find)
		return (add);
	return (NULL);
}
