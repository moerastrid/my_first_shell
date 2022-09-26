# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: ageels <ageels@student.codam.nl>             +#+                      #
#                                                    +#+                       #
#    Created: 2022/09/12 13:51:01 by ageels        #+#    #+#                  #
#    Updated: 2022/09/26 18:01:54 by ageels        ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME := minishell
USER = ageels
CFLAG = -I /Users/$(USER).brew/opt/readline/include
LFLAG = -L /Users/$(USER)/.brew/opt/readline/lib -lreadline
#-Wall -Werror -Wextra
SRC = 	src/main.c\
		src/execute_command.c\
		src/thefam.c\
		src/builtins00.c\
		src/parser.c\
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
	@$(CC) $(CFLAG) $(LFLAG) $(OBJ) -o $@
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
