# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ageels <ageels@student.codam.nl>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/12 13:51:01 by ageels            #+#    #+#              #
#    Updated: 2022/09/29 17:10:21 by tnuyten          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := minishell
BREW_DIR = $(shell brew --prefix)
CFLAG = -I $(BREW_DIR)/opt/readline/include -I lib/libft #-fsanitize=address -fno-omit-frame-pointer -g -O3 #-Wall -Wextra -Werror
LFLAG = -L $(BREW_DIR)/opt/readline/lib -lreadline -L lib/libft
CC = clang

SRC = 	src/main.c\
		src/prompt.c\
		src/parser.c\
		src/lexer/lexer.c\
		src/lexer/token.c\
		src/lexer/token_free.c\
		src/execute00.c\
		src/execute01.c\
		src/execute02.c\
		src/builtins00.c\
		src/path.c\

# OBJ_T = $(patsubst src/%.c,obj/%.o,$(SRC))
# OBJ = $(patsubst src/lexer/%.c,obj/lexer/%.o,$(OBJ_T))
OBJ = $(SRC:.c=.o)

#Colors:
GREEN		=	\e[38;5;118m
YELLOW		=	\e[38;5;226m
RESET		=	\e[0m
_SUCCESS	=	[$(GREEN)SUCCESS$(RESET)]
_INFO		=	[$(YELLOW)INFO$(RESET)]

all : libft $(NAME)

lib/libft/libft.a: libft

libft:
	@$(MAKE) -C lib/libft

$(NAME): $(OBJ) lib/libft/libft.a
	$(CC) $(OBJ) lib/libft/libft.a $(CFLAG) $(LFLAG) -o $(NAME)
	@printf "$(_SUCCESS) Minishell ready.\n"

obj/%.o : src/%.c
	@mkdir -pv obj
	$(CC) $(CFLAG) -o $@ -c $^

obj/lexer/%.o : src/lexer/%.c
	@mkdir -pv obj/lexer
	$(CC) $(CFLAG) -o $@ -c $^

clean :
	@test -e obj && rm -fr obj || printf "$(_INFO) No objects to clean \n"
	@test -e obj/lexer && rm -fr obj/lexer || printf "$(_INFO) No objects to clean \n"
		@$(MAKE) -C lib/libft clean

fclean : clean
	@rm -f $(NAME)
		@$(MAKE) -C lib/libft fclean

re : fclean all

.PHONY: all bonus libft clean fclean re


