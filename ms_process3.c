/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_process3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siychoi <siychoi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 21:30:03 by siychoi           #+#    #+#             */
/*   Updated: 2024/06/28 21:33:02 by siychoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_error_in_process(char **cmd, char **envp)
{
	if (access(cmd[0], F_OK) != 0)
		print_nofile_error(127, cmd[0]);
	else if (access(cmd[0], F_OK) == 0 && execve(cmd[0], cmd, envp) == -1)
		print_code_error(126, cmd[0]);
}
