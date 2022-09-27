# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: ageels <ageels@student.codam.nl>             +#+                      #
#                                                    +#+                       #
#    Created: 2022/09/12 13:51:01 by ageels        #+#    #+#                  #
#    Updated: 2022/09/27 20:50:48 by ageels        ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME := minishell
BREW_DIR = $(shell brew --prefix)
CFLAG = -I $(BREW_DIR)/opt/readline/include
LFLAG = -L $(BREW_DIR)/opt/readline/lib -lreadline
CC = clang
#-fsanitize=address -g -O3
#-Wall -Werror -Wextra
SRC = 	src/main.c\
		src/prompt.c\
		src/parser.c\
		src/token00.c\
		src/token01.c\
		src/execute00.c\
		src/execute01.c\
		src/execute02.c\
		src/builtins00.c\
		src/utils00.c\
		src/utils01.c\

#Colors:
GREEN		=	\e[38;5;118m
YELLOW		=	\e[38;5;226m
RESET		=	\e[0m
_SUCCESS	=	[$(GREEN)SUCCESS$(RESET)]
_INFO		=	[$(YELLOW)INFO$(RESET)]

all : $(NAME)

OBJ = $(patsubst src/%.c,obj/%.o,$(SRC))

$(NAME) : $(OBJ)
	$(CC) $(CFLAG) $(LFLAG) $(OBJ) -o $@
	@printf "$(_SUCCESS) Minishell ready.\n"

obj/%.o : src/%.c
	@mkdir -pv obj
	@$(CC) $(CFLAG) -o $@ -c $^

clean :
	@test -e obj && rm -fr obj || printf "$(_INFO) No objects to clean \n"

fclean : clean
	@rm -f $(NAME)

re : fclean all

.PHONY: all bonus libft clean fclean re
