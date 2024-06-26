/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siychoi <siychoi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 17:35:05 by siychoi           #+#    #+#             */
/*   Updated: 2024/07/01 16:01:05 by siychoi          ###   ########.fr       */
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
# include <signal.h>
# include <termios.h>
# include <fcntl.h>
# include "./Libft/get_next_line_bonus.h"
# include "./Libft/libft.h"
# include <sys/types.h>
# include <sys/stat.h>

typedef struct s_envp
{
	char			*key;
	char			*value;
	int				key_len;
	int				value_len;
	struct s_envp	*next;
}	t_envp;

typedef struct s_fd
{
	int	fd[2];
	int	temp_fd;
}	t_fd;

# define CNT 1
# define IN 2 
# define HD 3
# define OUT 4
# define APD 5
# define ERROR 6
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
	char			*infile_name;
	char			*outfile_name;
	int				infile_type;
	int				outfile_type;
	int				cnt;
	int				total_len;
	struct s_phrase	*next;
}	t_phrase;

typedef struct s_input
{
	t_phrase	*head;
	t_phrase	*tail;
	int			cnt;
	int			valid;
}	t_input;

typedef struct s_quote_flag
{
	int	s_quote;
	int	d_quote;
}	t_quote_flag;

typedef struct s_parsing_ptr
{
	char		*start;
	char		*end;
	int			len;
	int			eof;
}	t_parsing_ptr;

typedef struct s_expansion
{
	int		i;
	int		cnt;
	char	*str;
}	t_expansion;

/*-----envp1.c-----*/
int			envp_size(t_envp **my_envp);
void		envp_add_back(t_envp **my_envp, t_envp *new);
void		envp_arr_to_list(char **envp, t_envp **n);
char		**envp_list_to_arr(t_envp *my_envp);

/*-----envp2.c-----*/
void		change_value(t_envp **my_envp, char *key, char *value);
char		*find_key(t_envp **my_envp, char *str);
char		*find_value(t_envp **my_envp, char *str);

/*-----ms_exe.c-----*/
int			make_list(t_input *list, t_envp**my_envp, char *buffer, int flag);
void		exec_minishell(t_envp **my_envp);
int			exe_one_command(t_envp **my_envp, t_phrase *phrase);
int			wait_and_return(t_input *list, int last_code);
int			exe_only_builtout_cmd(t_envp **my_envp, t_phrase *phrase);

/*-----ms_builtin_cmd.c-----*/
int			is_builtin_cmd(t_phrase *phrase);
int			check_builtin_cmd(t_envp **my_envp, t_phrase *phrase);
int			exe_only_builtin_cmd(t_envp **my_envp, t_phrase *phrase);

/*-----ms_cd.c-----*/
int			ms_cd(t_envp **my_envp, char **argv);

/*-----ms_dollar.c-----*/
void		change_dollar_all_tokens(t_input *input, t_envp **my_envp);

/*-----ms_dollar_utils.c-----*/
char		*phrase_to_str(t_phrase *phrase);
void		expansion(t_envp **envp, t_phrase *phr, t_expansion *e, int flag);
void		quote_process(t_phrase *phrase, t_expansion *e, int *flag);
void		init_expansion_var(t_expansion *exp, t_token *token);

/*-----command_parsing.c-----*/
char		*find_path(char **env);
char		**cmd_split(char *str);
char		*cmd_strjoin(char const *s1, char const *s2, char *s3);
char		*remove_backslash(char *str);

/*-----error1.c-----*/
int			print_code_error(int code, char *cmd);
int			print_builtin_error(char *cmd, char *str);
int			print_code_error_builtin(int code, char *cmd);
void		check_process_error(t_phrase *phrase);
int			check_process_error_return(t_phrase *phrase);

/*-----error2.c-----*/
int			print_nofile_error(int code, char *cmd);
void		print_syntax_error(char	*ptr);
int			print_dir_error(char *cmd);
int			is_input_error(t_token *token);
int			is_output_error(t_token *token);

/*-----ms_echo.c-----*/
int			ms_echo(char **argv);
int			str_str_len(char **str);

/*-----ms_env.c-----*/
int			ms_env(t_envp **my_envp, char **argv);

/*-----ms_exit.c-----*/
int			ms_exit(char **argv);
int			ft_atol(const char *str, long long *num);

/*-----ms_export.c-----*/
int			ms_export(t_envp **my_envp, char **argv);
void		add_key_and_value(t_envp **my_envp, char *str, int idx);
void		print_envp(t_envp **my_envp);

/*-----ms_process1.c-----*/
void		first_process(t_envp **my_envp, t_phrase *phrase, t_fd p);
void		connect_process(t_envp **my_envp, t_phrase *phrase, t_fd p);
int			last_process(t_envp **my_envp, t_phrase *phrase, t_fd p);
int			child_process_exe(t_phrase *phrase, char **envp);
void		child_process_exe2(char **split_str, char **s_cmd, char **envp);

/*-----ms_process2.c-----*/
int			set_process(t_envp **my_envp, t_input *list);
int			make_pid(pid_t *pid);
void		close_all_pipe(t_fd p);
void		dup_io_fd(int *io_fd, t_fd p);
void		dup_and_close_last_process(int *io_fd, t_fd p);

/*-----ms_process3.c-----*/
void		check_error_in_process(char **cmd, char **envp);

/*-----ms_pwd.c-----*/
int			ms_pwd(char **argv);

/*-----ms_redirection1.c-----*/
void		skip_redirection(t_phrase *phrase);
char		*make_hd_file(t_token *token, int *flag);
void		make_hd_content(t_token *token, int fd, char *path);
void		open_outfile(t_phrase *phrase, int *io_fd);
int			open_in_and_out_fd(t_phrase *phrase, int *io_fd);

/*-----ms_redirection2.c-----*/
int			infile_to_filename(t_phrase *phrase, t_token *token, int *flag);
int			outfile_to_filename(t_phrase *phrase, t_token *token);
void		redirection_to_filename(t_input *input, int *flag);
int			check_rd_error(t_phrase *phrase, t_token *token, int *flag);
void		check_heredoc_exit(t_token *token, char *buffer, char *path);

/*-----ms_unset.c-----*/
int			ms_unset(t_envp **my_envp, char **argv);

/*-----utils.c-----*/
int			ms_strncmp(const char *s1, const char *s2, size_t n);
int			count_token_data(t_token *token, int *cnt);
char		**token_to_arr(t_phrase *phrase);
void		free_buffer_and_redirections(t_input *list, char *buffer);
void		free_2d_array(char **arr);

/*-----parse_lexer.c-----*/
void		change_stat(int *flag);
t_input		*lexer(char *str);

/*-----parse_struct_token.c-----*/
t_token		*get_token(int type, t_parsing_ptr *ptr);
void		add_token_back(t_phrase *phrase, t_parsing_ptr *ptr);
void		add_token_rd(t_phrase *phrase, t_parsing_ptr *ptr, int type);
void		add_token(t_phrase *phrase, char *str, int *len);

/*-----parse_struct_phrase.c-----*/
t_phrase	*get_phrase(void);
void		add_phrase(t_input *list, t_parsing_ptr *ptr);
void		delete_front(t_input *list);

/*-----parse_struct_input.c-----*/
t_input		*get_input(t_parsing_ptr *ptr);
void		free_phrase(t_phrase *phrase);
void		free_input(t_input *list);

/*-----parse_pointer.c-----*/
void		init_ptr(t_parsing_ptr *ptr, char *str);
void		set_start(t_parsing_ptr *ptr);
void		move_start(t_parsing_ptr *ptr);
int			move_end(t_parsing_ptr *ptr);

/*-----parse_discriminant.c-----*/
int			is_space(char ch);
int			is_pipe(t_input *list, char *str, char start);
int			is_discriminant(char ch);
int			is_quote(t_parsing_ptr *ptr);
void		add_quote(t_input *list, t_parsing_ptr *ptr, t_quote_flag *flag);

/*-----parse_add_redirection.c-----*/
void		add_redirection(t_input *list, t_parsing_ptr *ptr);

/*-----parse_essentials.c-----*/
void		init_quote_flag(t_quote_flag *flag);
t_input		*initial_process(char *str, t_quote_flag *flag, t_parsing_ptr *ptr);
t_input		*final_process(t_input *list);

/*-----signal.c-----*/
void		set_signal(int signo, void *handler);
void		set_interactive_signal(void);
void		set_wait_signal(void);
void		set_child_signal(void);
void		set_hd_signal(void);

/*-----signal_handler.c-----*/
int			print_signal_exit_status(int signo);
void		catch_int(void);
void		catch_int_hd(void);
void		echo_ctrl(void);
void		display_ctrl(void);

#endif