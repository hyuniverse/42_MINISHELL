/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siychoi <siychoi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 17:24:50 by siychoi           #+#    #+#             */
/*   Updated: 2024/06/26 17:30:48 by siychoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//void	leaks(void)
//{
//	system("leaks minishell");
//}

int	main(int argc, char *argv[], char *envp[])
{
	t_envp	*my_envp;

	//atexit(leaks);
	if (argc != 1 || argv[0] == NULL)
		exit(1);
	my_envp = NULL;
	envp_arr_to_list(envp, &my_envp);
	exec_minishell(&my_envp);
	return (0);
}
