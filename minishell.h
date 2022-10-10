/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: ageels <ageels@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/27 22:19:40 by ageels        #+#    #+#                 */
/*   Updated: 2022/10/10 15:37:10 by ageels        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>
# include <sys/stat.h>
// # include <sys/syslimits.h> Only works on MacOS.
# include <stdlib.h>
# include <signal.h>
# include <stdbool.h>
# include <curses.h>
# include <term.h>

// Libft
# include "lib/libft/libft.h"

//STRUCTS:
typedef struct s_children {
	pid_t				id;
	struct s_children	*next;
}	t_children;

typedef struct s_simple {
	char			**argv;
	int				argc;
	char			*bin;
	struct s_simple	*next;
}	t_simple;

typedef struct s_str_list
{
	char				*str;
	int					append_mode;
	struct s_str_list	*next;
}	t_str_list;

typedef struct s_cmd {
	int			cmd_count;
	t_simple	*simples;
	t_str_list	*outfiles;
	t_str_list	*infiles;
	t_str_list	*delimiters;
	char		**paths;
	char		**envp;
}	t_cmd;

enum	 e_token_type {
	WORD = 0,
	GREAT = 1,
	LESS = 2,
	PIPE = 3,
	GREATGREAT = 4,
	LESSLESS = 5,
	DOLL = 6,
	DOLLQ = 7,
	QUOT = 8,
	DQUOT = 9
};

typedef struct s_token {
	enum e_token_type	type;
	char				*data;
	struct s_token		*next;
}	t_token;

# include "src/lexer/lexer.h"

// GLOBAL VAR
t_children	*g_children;

// FILES & FUNCTIONS:
//prompt
char		*prompt(void);

// LEXER
// lexer.c
	t_token	*tokenize(char *input);

// PARSER
// parser.c
int			parse(t_token *tokens, t_cmd *cmds);

// cmd_builder.c
void		add_outfile(t_cmd *cmd, int append_mode, char *data);
void		add_infile(t_cmd *cmd, char *data);
void		add_delimiter(t_cmd *cmd, char *data);
int			add_arg(t_simple *simple, char *arg);

// simple.c
t_simple	*new_simple(int argc, char **argv);
void		simple_add_back(t_simple **lst, t_simple *new_elem);
t_simple	*new_simple(int argc, char **argv);
void		free_simples(t_simple *simples);
int			set_bin(t_cmd *cmd, t_simple *simple);

//buildins (00)
void		bi_echo(void);
void		bi_cd(void);
void		bi_pwd(void);
void		bi_export(void);
void		bi_unset(void);
void		bi_env(void);
void		bi_exit(void);

//EXECUTER
int			execute(t_cmd cmds);

// global kids
void		free_children(t_children *root);
t_children	*new_child(pid_t id);
void		child_add_back(t_children *root, t_children *new);
void		kill_children(t_children *kids);

// SUBSTITUTOR
// substitute.c
void		substitute(t_token *tokens, char **envp);


//signals
void		catch_signals(void);

//utils
char		**single_split(char const *s, char c);

//path
char		**getpaths(char **envp);

//str_list
t_str_list	*str_list_new(char *str, int append_mode);
void		str_list_add_back(t_str_list *root, t_str_list *new);
void		free_str_list(t_str_list *root);

//DEBUG #TODO REMOVE... ILLEGAL FUNCTION!
void		print_token_type(enum e_token_type num);
void		print_str_list(t_str_list *root, int mode);
void		print_tokens(t_token *root);
void		print_simples(t_cmd *cmd);
void		print_children(t_children *root);
void		run_leaks(void);
void		run_lsof(void);
void		run_cat_fd(void);
void		close_all(void);

#endif
