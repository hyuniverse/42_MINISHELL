/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siychoi <siychoi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 17:24:50 by siychoi           #+#    #+#             */
/*   Updated: 2024/06/29 14:22:02 by siychoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check()
{
	system("leaks --list -- minishell");
}

int	main(int argc, char *argv[], char *envp[])
{
	t_envp	*my_envp;

	//atexit(check);
	if (argc != 1 || argv[0] == NULL)
		exit(1);
	my_envp = NULL;
	envp_arr_to_list(envp, &my_envp);
	set_interactive_signal();
	exec_minishell(&my_envp);
	//atexit(check);
	return (0);
}
