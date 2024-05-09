/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_discriminant.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehyupar <sehyupar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 22:05:11 by sehyupar          #+#    #+#             */
/*   Updated: 2024/05/09 22:05:19 by sehyupar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_space(char ch)
{
	if ((ch >= 9 && ch <= 13) || ch == 32)
		return (TRUE);
	return (FALSE);
}
int	is_command()
{

	return (TRUE);
}

int	is_pipe()
{

	return (TRUE);
}

int	is_redirection()
{

	return (TRUE);
}