/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehyupar <sehyupar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 18:29:26 by sehyupar          #+#    #+#             */
/*   Updated: 2024/05/10 18:31:54 by sehyupar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>

// token type, Binding power
# define CNT 1
# define CMD 2
# define PIPE 3
# define RD 4
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
	int				type;
	int				cnt;
	struct s_phrase	*next;
}	t_phrase;

typedef struct s_input
{
	t_phrase	*head;
	t_phrase	*tail;
	int			cnt;
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

t_input	*lexer(char *str);
t_token	*get_token(int type, t_parsing_ptr *ptr);
t_input	*get_input(t_parsing_ptr *ptr);
void	add_phrase(t_input *list, t_parsing_ptr *ptr);
void	add_token_back(t_phrase *phrase, t_parsing_ptr *ptr);
void	add_token_front(t_phrase *phrase, t_parsing_ptr *ptr);
void	init_ptr(t_parsing_ptr *ptr, char *str);
void	set_start(t_parsing_ptr *ptr);
void	move_start(t_parsing_ptr *ptr);
void	move_end(t_parsing_ptr *ptr);
void	free_input(t_input *list);
int		is_space(char ch);
void	print_phrase(t_phrase *phrase);

#endif