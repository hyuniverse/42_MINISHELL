/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siychoi <siychoi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 09:50:43 by siychoi           #+#    #+#             */
/*   Updated: 2023/11/01 18:13:05 by siychoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	digit_num(long long n)
{
	int	cnt;

	cnt = 0;
	if (n < 0)
		n = -n;
	else if (n == 0)
		cnt = 1;
	while (n > 0)
	{
		n = n / 10;
		cnt++;
	}
	return (cnt);
}

char	*ft_itoa(int n)
{
	char		*result;
	int			sign;
	int			i;
	long long	num;

	sign = 0;
	num = n;
	if (num < 0)
	{
		sign = 1;
		num = -num;
	}
	result = (char *)malloc(sizeof(char) * (digit_num(num) + sign + 1));
	if (!result)
		return (NULL);
	i = digit_num(num) + sign;
	result[i--] = '\0';
	while (i >= 0)
	{
		result[i--] = num % 10 + '0';
		num = num / 10;
	}
	if (sign == 1)
		result[0] = '-';
	return (result);
}
