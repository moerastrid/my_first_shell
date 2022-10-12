/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: ageels <ageels@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/27 22:19:40 by ageels        #+#    #+#                 */
/*   Updated: 2022/10/12 19:26:50 by ageels        ########   odam.nl         */
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

# include "lib/libft/libft.h"
# include "src/display/display.h"

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

// GLOBAL VAR
t_children		*g_children;
unsigned int	g_errno;

// FILES & FUNCTIONS:

// buildins
int			bi_echo(t_simple *simple);
int			bi_cd(void);
int			bi_pwd(t_cmd cmd);
int			bi_export(void);
int			bi_unset(void);
int			bi_env(t_cmd cmd);
void		bi_exit(t_cmd cmd, t_token *tokens);

// execute
int			execute(t_cmd cmds, t_token *tokens);

// lexer
t_token		*tokenize(char *input);
void		free_token_list(t_token *token);
void		reset(t_cmd *cmd, t_children *kids, t_token *tokens);

// parser
void		free_str_list(t_str_list *root);
void		free_simples(t_simple *simples);
int			parse(t_token *tokens, t_cmd *cmds);

// setup_reset
char		**getpaths(char **envp);
int			setup(t_cmd *cmd, char **envp);
void		reset(t_cmd *cmd, t_children *kids, t_token *tokens);
void		clear_cmd(t_cmd *cmd);

// substitutor
void		substitute(t_token *tokens, char **envp);
void		redirect_outfile(t_str_list *outfiles);

// global kids
void		free_children(t_children *root);
t_children	*new_child(pid_t id);
void		child_add_back(t_children *root, t_children *new);
void		kill_children(t_children *kids);

//utils
char		**single_split(char const *s, char c);

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
