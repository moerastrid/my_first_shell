# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: ageels <ageels@student.codam.nl>             +#+                      #
#                                                    +#+                       #
#    Created: 2022/09/12 13:51:01 by ageels        #+#    #+#                  #
#    Updated: 2022/09/29 21:13:26 by ageels        ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME := minishell
BREW_DIR = $(shell brew --prefix)
OBJ_DIR = ./obj
CFLAG = -I $(BREW_DIR)/opt/readline/include -I lib/libft #-fsanitize=address -fno-omit-frame-pointer -g -O3 #-Wall -Wextra -Werror
LFLAG = -L $(BREW_DIR)/opt/readline/lib -lreadline  -L lib/libft
CC = clang

SRC =	src/main.c\
		src/prompt.c\
		src/path.c\
		src/lexer/lexer.c\
		src/lexer/token.c\
		src/lexer/token_free.c\
		src/parser/parser.c\
		src/parser/str_list.c\
		src/execute/execute00.c\
		src/execute/execute01.c\
		src/execute/execute02.c\
		src/builtins/builtins00.c\
		src/utils/utils00.c

OBJ = $(patsubst src/%.c,obj/%.o,$(SRC))
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

$(NAME): $(OBJ) libft
	@$(CC) $(CFLAG) -o $(NAME) $(OBJ) $(LFLAG) lib/libft/libft.a
	@printf "$(_SUCCESS) Minishell ready.\n"

obj/%.o : src/%.c 
	@mkdir -pv obj
	@mkdir -pv obj/lexer
	@mkdir -pv obj/execute
	@mkdir -pv obj/builtins
	@mkdir -pv obj/utils
	@mkdir -pv obj/parser
	@$(CC) $(CFLAG) -o $@ -c $^

clean :
	@test -e obj && rm -fr obj || printf "$(_INFO) No objects to clean \n"
	@$(MAKE) -C lib/libft clean

fclean : clean
	@rm -f $(NAME)
	@$(MAKE) -C lib/libft fclean

re : fclean all

.PHONY: all bonus libft clean fclean re
