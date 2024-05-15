# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: siychoi <siychoi@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/24 13:34:50 by siychoi           #+#    #+#              #
#    Updated: 2024/05/01 17:34:03 by siychoi          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= libft.a
CC			= cc
CFLAG		= -Wall -Wextra -Werror
RM			= rm
RMFLAG		= -f
AR			= ar
ARFLAGS		= crs
INCLUDE		= -Iincludes
SRC_DIR		= ./
SRCS		= ft_atoi.c ft_bzero.c ft_calloc.c ft_isalnum.c ft_isalpha.c ft_isascii.c ft_isprint.c ft_isdigit.c ft_itoa.c ft_memchr.c ft_memcmp.c ft_memcpy.c ft_memmove.c ft_memset.c ft_putchar_fd.c ft_putendl_fd.c ft_putstr_fd.c ft_split.c ft_strchr.c ft_strdup.c ft_striteri.c ft_strjoin.c ft_strlcat.c ft_strlcpy.c ft_strlen.c ft_strmapi.c ft_strncmp.c ft_strnstr.c ft_strrchr.c ft_strtrim.c ft_substr.c ft_tolower.c ft_toupper.c get_next_line_bonus.c get_next_line_utils_bonus.c
SRCS_BONUS	= ft_lstadd_back_bonus.c ft_lstadd_front_bonus.c ft_lstclear_bonus.c ft_lstdelone_bonus.c ft_lstiter_bonus.c ft_lstlast_bonus.c ft_lstmap_bonus.c ft_lstnew_bonus.c ft_lstsize_bonus.c
OBJS		= $(SRCS:.c=.o)
OBJS_BONUS	= $(SRCS_BONUS:.c=.o)

all : $(NAME)

clean :
		$(RM) $(RMFLAG) $(OBJS) $(OBJS_BONUS) BONUS_NAME

fclean :
		$(RM) $(RMFLAG) $(OBJS) $(OBJS_BONUS) BONUS_NAME $(NAME)

re : fclean all

bonus : BONUS_NAME

BONUS_NAME : $(OBJS_BONUS)
		$(AR) $(ARFLAGS) $(NAME) $^
		touch $@

%.o : %.c
		$(CC) $(CFLAG) -c $< -o $@ $(INCLUDE)

$(NAME) : $(OBJS)
		$(AR) $(ARFLAGS) $@ $^

.PHONY : all clean fclean re