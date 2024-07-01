/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siychoi <siychoi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 17:24:50 by siychoi           #+#    #+#             */
/*   Updated: 2024/07/01 15:36:21 by siychoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char *argv[], char *envp[])
{
	t_envp	*my_envp;

	if (argc != 1 || argv[0] == NULL)
		exit(1);
	my_envp = NULL;
	envp_arr_to_list(envp, &my_envp);
	set_interactive_signal();
	exec_minishell(&my_envp);
	return (0);
}
