/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siychoi <siychoi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 17:35:05 by siychoi           #+#    #+#             */
/*   Updated: 2024/05/10 12:40:00 by siychoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <unistd.h>
# include <sys/errno.h>
# include <string.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <dirent.h>
# include "./Libft/get_next_line_bonus.h"
# include "./Libft/libft.h"

typedef struct s_envp
{
	char			*key;
	char			*value;
	struct s_envp	*next;
}	t_envp;

/*-----envp.c-----*/
int		envp_size(t_envp **my_envp);
void	envp_add_back(t_envp **my_envp, t_envp *new);
void	envp_arr_to_list(char **envp, t_envp **n);
char	**envp_list_to_arr(t_envp **my_envp);
void	change_envp_value(t_envp **my_envp, char *key, char *value);

/*-----minishell.c-----*/
int		child_process(char *cmd, t_envp **my_envp);
int		child_process_exe(char *cmd, char **envp);
int		check_builtin_cmd(t_envp **my_envp, char *cmd);

/*-----ms_cd.c-----*/
int		ms_cd(t_envp **my_envp, char **argv);
char	*find_value(t_envp **my_envp, char *str);
char	*find_key(t_envp **my_envp, char *str);

/*-----command_parsing.c-----*/
char	*find_path(char **env);
char	**cmd_split(char *str);
char	*cmd_strjoin(char const *s1, char const *s2, char *s3);
char	*remove_backslash(char *str);

/*-----error.c-----*/
int		print_code_error(int code, char *cmd);
int		print_builtin_error(char *cmd, char *str);
int		print_code_error_builtin(int code, char *cmd);

/*-----ms_echo.c-----*/
int		ms_echo(char **argv);
int		str_str_len(char **str);

/*-----ms_env.c-----*/
int		ms_env(t_envp **my_envp, char **argv);

/*-----ms_exit.c-----*/
int		ms_exit(char **argv);
int		ft_atol(const char *str, long long *num);

/*-----ms_export.c-----*/
int		ms_export(t_envp **my_envp, char **argv);
void	add_key_and_value(t_envp **my_envp, char *str, int equal_idx);
void	print_envp(t_envp **my_envp);

/*-----ms_pwd.c-----*/
int		ms_pwd(char **argv);

/*-----ms_unset.c-----*/
int		ms_unset(t_envp **my_envp, char **argv);

/*-----utils.c-----*/
int		ms_strncmp(const char *s1, const char *s2, size_t n);

#endif