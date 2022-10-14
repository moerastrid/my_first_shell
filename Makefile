NAME := minishell
BREW_DIR = $(shell brew --prefix)
OBJ_DIR = ./obj
CFLAG = -I $(BREW_DIR)/opt/readline/include -I lib/libft -fsanitize=address -g -O3 -fno-omit-frame-pointer #-Wall -Wextra -Werror
LFLAG = -L $(BREW_DIR)/opt/readline/lib -lreadline  -L lib/libft
CC = clang

SRC =	src/main.c\
		src/display/prompt.c\
		src/display/signals.c\
		src/display/errors.c\
		src/lexer/lexer.c\
		src/lexer/token.c\
		src/lexer/token_free.c\
		src/parser/parser.c\
		src/parser/simple.c\
		src/parser/str_list.c\
		src/parser/cmd_builder.c\
		src/substitutor/substitutor.c\
		src/substitutor/substitute_dquot.c\
		src/execute/builtins/cd.c\
		src/execute/builtins/echo.c\
		src/execute/builtins/env.c\
		src/execute/builtins/exit.c\
		src/execute/builtins/export.c\
		src/execute/builtins/pwd.c\
		src/execute/builtins/unset.c\
		src/execute/call_builtin.c\
		src/execute/children.c\
		src/execute/execute.c\
		src/execute/family_life.c\
		src/execute/redirect.c\
		src/execute/single.c\
		src/execute/touch_children.c\
		src/setup_reset/path.c\
		src/setup_reset/setup.c\
		src/setup_reset/reset.c\
		src/utils/utils00.c\
		src/debug/print.c\

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
	@mkdir -pv obj/display
	@mkdir -pv obj/lexer
	@mkdir -pv obj/execute
	@mkdir -pv obj/execute/builtins
	@mkdir -pv obj/utils
	@mkdir -pv obj/parser
	@mkdir -pv obj/substitutor
	@mkdir -pv obj/debug
	@mkdir -pv obj/setup_reset
	@$(CC) $(CFLAG) -o $@ -c $^

clean :
	@test -e obj && rm -fr obj || printf "$(_INFO) No objects to clean \n"
	@$(MAKE) -C lib/libft clean

fclean : clean
	@rm -f $(NAME)
	@$(MAKE) -C lib/libft fclean

re : fclean all

.PHONY: all bonus libft clean fclean re
