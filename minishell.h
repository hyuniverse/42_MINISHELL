/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehyupar <sehyupar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 18:29:26 by sehyupar          #+#    #+#             */
/*   Updated: 2024/05/07 21:47:16 by sehyupar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <string.h>
# include <stdlib.h>

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
	char	*data;
	int		type;
}	t_token;

typedef struct s_lexing_flag
{
	int	cmd;
	int	s_quote;
	int	d_quote;
}	t_lexing_flag;

#endif