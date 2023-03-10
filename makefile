# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aaammari <aaammari@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/07 18:45:14 by aaammari          #+#    #+#              #
#    Updated: 2023/03/05 16:42:31 by aaammari         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #



LIB_LIBFT = libft/libft.a
HEADER = libft/libft.h minishell.h

NAME = minishell
SRC =	minishell.c 		\
		check_quotes.c		\
		expand.c			\
		redirect.c			\
		redir_append.c		\
		utils_dollar_qts.c	\
		expand_utils.c		\
		ft_exec.c			\
		ft_exec_pipe.c		\
		utils_exec.c		\
		redirections.c		\
		builtins_cmd.c		\
		ft_cd.c				\
		ft_unset.c			\
		env_utils.c			\

OBJ = $(SRC:.c=.o)

%.o : %.c $(HEADER) 
	gcc -Wall -Wextra -Werror -c $< -o $@

all : LIBFTT $(NAME)

$(NAME) :  $(OBJ) 
	gcc -Wall -Wextra -Werror -o $(NAME) $(OBJ) $(LIB_LIBFT) -lreadline
	
LIBFTT : 
	make -C libft

clean :
	rm -f $(NAME) $(OBJ)
	make clean -C LIBFT
	
fclean : clean
	make fclean -C LIBFT

re : fclean all