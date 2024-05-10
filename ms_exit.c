/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siychoi <siychoi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 13:52:48 by siychoi           #+#    #+#             */
/*   Updated: 2024/05/10 12:41:30 by siychoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// error_code는 '$?' 명령어로 확인 가능
// 범위 0~255 (exit(300) 했을 경우 overflow되어 44가 반환)
int	ms_exit(char **argv)
{
	char		exit_code;
	long long	num;

	if (argv[1] == NULL)
		exit(0);
	else if (ft_atol(argv[1], &num) == 0)
	{
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(argv[1], 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		exit(255);
	}
	else if (argv[2] != NULL)
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		exit_code = 1;
	}
	else
		exit((char)num);
	return ((int)exit_code);
}

int	ft_atol(const char *s, long long *num)
{
	unsigned long long	t_n;
	unsigned long long	m_n;
	size_t				i;
	int					sign;

	t_n = 0;
	i = 0;
	sign = 1;
	while ((s[i] >= 9 && s[i] <= 13) || (s[i] == 32))
		i++;
	if (s[i] == '-' || s[i] == '+')
		if (s[i++] == '-')
			sign = -sign;
	m_n = 9223372036854775807 + (sign < 0);
	while (s[i] >= '0' && s[i] <= '9')
	{
		t_n = t_n * 10 + (s[i] - '0');
		if (t_n > m_n || (t_n == (m_n / 10) && (s[i] - '0') > (int)(m_n % 10)))
			return (0);
		i++;
	}
	if (i != ft_strlen(s))
		return (0);
	*num = (long long)(t_n * sign);
	return (1);
}
