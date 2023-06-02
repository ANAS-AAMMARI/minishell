# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aaammari <aaammari@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/07 18:45:14 by aaammari          #+#    #+#              #
#    Updated: 2023/03/22 15:59:21 by aaammari         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = minishell

HEADER = headers/executions.h headers/parsing.h

LIB_H = libft/libft.h

LIBFT = libft/libft.a

INCLUDE_READLINE =$(READLINE)/include

LIB_READLINE = $(READLINE)/lib

READLINE = $(shell brew --prefix readline)

CC = gcc -Wall -Wextra -Werror

SRCEXEC = exec/ft_exec.c		\
		exec/ft_exec_pipe.c		\
		exec/utils_exec.c		\
		exec/redirections.c		\
		exec/builtins_cmd.c		\
		exec/ft_cd.c			\
		exec/ft_unset.c			\
		exec/env_utils.c		\
		exec/exec_one_red.c		\
		exec/utils_red.c		\
		exec/get_next_line.c	\
		exec/herdoc.c			\
		exec/utils2_exec.c		\
		exec/ft_export.c		\
		exec/ft_signal.c		\
		exec/ft_signal1.c		\
		exec/utils_export.c		\
		exec/utils_pipe.c		\
		exec/utils3_exec.c		\
		exec/ft_free.c			\
		exec/ft_cd_dash.c		\

SRCPARSER = parse/check_quotes.c	\
		parse/expand.c				\
		parse/redirect.c			\
		parse/redir_append.c		\
		parse/utils_dollar_qts.c	\
		parse/expand_utils.c		\
		parse/utils.c				\
		parse/check_pipes.c			\
		parse/check_redirect.c		\
		parse/parse.c				\
		parse/red_parse.c			\
		parse/nb_arg_red.c			\
		parse/fill_red.c			\
		parse/init.c				\
		parse/utils_2.c				\

MAIN = minishell.c \

SRC = $(MAIN) $(SRCPARSER) $(SRCEXEC)
 
OBJ = $(SRC:.c=.o)

%.o:%.c $(HEADER) $(LIB_H)
	$(CC) -I $(INCLUDE_READLINE) -c $< -o $@

all:$(NAME)

$(NAME):$(HEADER) $(LIB_H) $(LIBFT) $(OBJ)
	$(CC) $(OBJ) -I $(INCLUDE_READLINE)  -L $(LIB_READLINE)  $(LIBFT) -o $(NAME) -lreadline

$(LIBFT):
	@make bonus -C libft

clean:
	@rm -rf $(OBJ)
	make clean -C libft

fclean:clean
	@rm -rf $(NAME)
	make fclean -C libft

re:fclean all

.PHONY: all clean fclean re