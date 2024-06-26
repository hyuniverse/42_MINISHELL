# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: siychoi <siychoi@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/01 17:23:47 by siychoi           #+#    #+#              #
#    Updated: 2024/06/26 16:48:15 by siychoi          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= minishell
CC			= cc
CFLAGS		= -Wall -Wextra -Werror -fsanitize=address -g
RM			= rm
RMFLAG		= -f
AR			= ar
ARFLAGS		= crs
SRC			= minishell command_split command_parsing envp error1 error2 ms_builtin_cmd \
			  ms_dollar ms_cd ms_echo ms_env ms_exit ms_export ms_process1 ms_process2 ms_pwd \
			  ms_redirection1 ms_redirection2 ms_unset utils \
			  parse_discriminant parse_lexer parse_pointer \
			  parse_struct_input parse_struct_phrase parse_struct_token \
			  parse_essentials signal
SRCS		= $(addsuffix .c, $(SRC))
OBJS		= $(SRCS:.c=.o)

all : $(NAME)

clean :
		$(RM) $(RMFLAG) $(OBJS) $(OBJS_BONUS) BONUS_NAME
		make -C Libft clean

fclean :
		$(RM) $(RMFLAG) $(OBJS) $(OBJS_BONUS) $(NAME) BONUS_NAME
		make -C Libft fclean

re : fclean
	$(MAKE) all

%.o : %.c
		$(CC) $(CFLAGS) -c $< -o $@ $(INCLUDE)

$(NAME) : $(OBJS)
		make -C Libft
		$(CC) $(CFLAGS) -o $@ $^ -LLibft -lft -lreadline

.PHONY : all clean fclean re bonus