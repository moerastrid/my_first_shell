/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ageels <ageels@student.codam.nl>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 22:19:40 by ageels            #+#    #+#             */
/*   Updated: 2022/10/14 18:40:58 by tnuyten          ###   ########.fr       */
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
# include <errno.h>

# include "lib/libft/libft.h"
# include "src/display/display.h"
# include "src/lexer/token.h"

//STRUCTS:

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
	t_token		*tokens;
	char		**paths;
	char		**envc;
}	t_cmd;

//typedef struct s_token {
//	enum e_token_type	type;
//	char				*data;
//	struct s_token		*next;
//}	t_token;

// GLOBAL VAR
int	g_errno;

// FILES & FUNCTIONS:
//display
char		*prompt(t_cmd	*cmd);

// execute
int			execute(t_cmd *cmds);

// lexer
t_token		*tokenize(char *input);
void		free_token_list(t_token *token);

// parser
void		free_str_list(t_str_list *root);
void		free_simples(t_simple *simples);
int			parse(t_cmd *cmds);

// setup_reset
char		**getpaths(char **envp);
int			setup(t_cmd *cmd, char **envp, int argc);
void		reset(t_cmd *cmd, char *line);
void		clear_cmd(t_cmd *cmd);

// substitutor
void		substitute(t_token *tokens, char **envp);
void		redirect_outfile(t_str_list *outfiles);

//utils
char		**single_split(char const *s, char c);

//DEBUG #TODO REMOVE... ILLEGAL FUNCTION!
void		print_token_type(enum e_token_type num);
void		print_str_list(t_str_list *root, int mode);
//void		print_tokens(t_token *root); (in token.h)
void		print_simples(t_cmd *cmd);
void		run_leaks(void);
void		run_lsof(void);
void		run_cat_fd(void);
void		close_all(void);

char	**env_add(char *to_add, char **envp);
char	**env_remove(char *var_name, char **envp);

#endif
