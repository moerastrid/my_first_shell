# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ageels <ageels@student.codam.nl>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/12 13:51:01 by ageels            #+#    #+#              #
#    Updated: 2022/09/26 12:56:54 by tnuyten          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := minishell
CFLAG := #-Wall -Werror -Wextra
SRC = 	src/main.c\
		src/execute_command.c\
		src/thefam.c\
		src/builtins00.c\

#Colors:
GREEN		=	\e[38;5;118m
YELLOW		=	\e[38;5;226m
RESET		=	\e[0m
_SUCCESS	=	[$(GREEN)SUCCESS$(RESET)]
_INFO		=	[$(YELLOW)INFO$(RESET)]

all : libft $(NAME)

OBJ = $(patsubst src/%.c,obj/%.o,$(SRC))

libft:
	@make -C libft
	@printf "$(_SUCCESS) Libft ready.\n"

$(NAME) : $(OBJ)
	@$(CC) $(CFLAG) $(OBJ) -o $@ -Llibft -lft -lreadline
	@printf "$(_SUCCESS) Minishell ready.\n"

obj/%.o : src/%.c
	@mkdir -pv obj
	@$(CC) $(CFLAG) -o $@ -c $^

clean :
	@test -e obj && rm -fr obj || printf "$(_INFO)  No objects to clean \n"
	@make -C libft clean

fclean : clean
	@rm -f $(NAME)
	@make -C libft fclean

re : fclean all

.PHONY: all bonus libft clean fclean re
