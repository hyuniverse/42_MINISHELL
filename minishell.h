/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehyupar <sehyupar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 17:35:05 by siychoi           #+#    #+#             */
/*   Updated: 2024/05/16 15:27:04 by sehyupar         ###   ########.fr       */
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

// token type, Binding power
# define CNT 1
# define CMD 2
# define RD 3
# define HD 4
# define DOUBLE_QUOTE 34
# define SINGLE_QUOTE 39

# define TRUE 1
# define FALSE 0

typedef struct s_token
{
	char			*data;
	int				type;
	struct s_token	*next;
}	t_token;

typedef struct s_phrase
{
	t_token			*head;
	t_token			*tail;
	t_token			*rd;
	int				type;
	int				cnt;
	struct s_phrase	*next;
}	t_phrase;

typedef struct s_input
{
	t_phrase	*head;
	t_phrase	*tail;
	int			cnt;
	int			valid;
}	t_input;

typedef struct s_lexing_flag
{
	int	cmd;
	int	s_quote;
	int	d_quote;
}	t_lexing_flag;

typedef struct s_parsing_ptr
{
	char	*start;
	char	*end;
	int		len;
	int		eof;
}	t_parsing_ptr;

/*-----envp.c-----*/
int		envp_size(t_envp **my_envp);
void	envp_add_back(t_envp **my_envp, t_envp *new);
void	envp_arr_to_list(char **envp, t_envp **n);
char	**envp_list_to_arr(t_envp **my_envp);
void	change_value(t_envp **my_envp, char *key, char *value);

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
void	add_key_and_value(t_envp **my_envp, char *str, int idx);
void	print_envp(t_envp **my_envp);

/*-----ms_pwd.c-----*/
int		ms_pwd(char **argv);

/*-----ms_unset.c-----*/
int		ms_unset(t_envp **my_envp, char **argv);

/*-----utils.c-----*/
int		ms_strncmp(const char *s1, const char *s2, size_t n);

/*-----parse_lexer.c-----*/
t_input	*lexer(char *str);

/*-----parse_struct_token.c-----*/
t_token	*get_token(int type, t_parsing_ptr *ptr);
void	add_token_back(t_phrase *phrase, t_parsing_ptr *ptr);
void	add_token_rd(t_phrase *phrase, t_parsing_ptr *ptr);

/*-----parse_struct_phrase.c-----*/
void	add_phrase(t_input *list, t_parsing_ptr *ptr);
void	delete_front(t_input *list);

/*-----parse_struct_input.c-----*/
t_input	*get_input(t_parsing_ptr *ptr);
void	free_input(t_input *list);

/*-----parse_pointer.c-----*/
void	init_ptr(t_parsing_ptr *ptr, char *str);
void	set_start(t_parsing_ptr *ptr);
void	move_start(t_parsing_ptr *ptr);
void	move_end(t_parsing_ptr *ptr);

/*-----parse_discriminant.c-----*/
int		is_space(char ch);
int		is_pipe(t_input *list, char *str);
int		is_discriminant(char ch);

void	print_phrase(t_phrase *phrase);

#endif