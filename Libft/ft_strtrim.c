/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siychoi <siychoi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 12:13:55 by siychoi           #+#    #+#             */
/*   Updated: 2023/11/04 19:47:56 by siychoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	front_trim(char const *s1, char const *set)
{
	int	cnt;
	int	i;
	int	j;
	int	flag;

	cnt = 0;
	i = 0;
	flag = 1;
	while (flag != 0)
	{
		flag = 0;
		j = 0;
		while (set[j])
		{
			if (s1[i] == set[j])
			{
				cnt++;
				flag = 1;
				break ;
			}
			j++;
		}
		i++;
	}
	return (cnt);
}

int	rear_trim(char const *s1, char const *set)
{
	int	cnt;
	int	i;
	int	j;
	int	flag;

	flag = 1;
	cnt = 0;
	i = ft_strlen(s1) - 1;
	while (flag != 0)
	{
		j = 0;
		flag = 0;
		while (set[j])
		{
			if (s1[i] == set[j])
			{
				cnt++;
				flag = 1;
				break ;
			}
			j++;
		}
		i--;
	}
	return (cnt);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*temp;
	int		front;
	int		i;
	int		s1_len;
	int		temp_size;

	i = 0;
	if (s1 == NULL || set == NULL)
		return (ft_calloc(1, 1));
	s1_len = ft_strlen(s1);
	front = front_trim(s1, set);
	if (s1_len == front)
		return (ft_calloc(1, 1));
	temp_size = s1_len - rear_trim(s1, set) - front + 1;
	temp = (char *)malloc(sizeof(char) * temp_size);
	if (!temp)
		return (NULL);
	ft_strlcpy(temp, s1 + front, temp_size);
	return (temp);
}
