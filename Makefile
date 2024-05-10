CC		=	cc
CFLAGS	=	-Wall -Werror -Wextra
NAME = minishell
SRCS = ms_lexer.c ms_methods_input.c ms_methods_parsing.c ms_methods_phrase.c\
	   ms_methods_token.c ms_discriminant.c test.c
OBJS = ms_lexer.o ms_methods_input.o ms_methods_parsing.o ms_methods_phrase.o\
	   ms_methods_token.o ms_discriminant.o test.o
INCLUDE = minishell.h

all: $(NAME)

%.o: %.c 
	$(CC) $(CFLAGS) -c $< -o $@ 

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(CLIB) $(SRCS) -o $(NAME)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re:
	make fclean
	make all

.PHONY: all, clean, fclean, re