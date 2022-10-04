/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: ageels <ageels@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/27 22:19:40 by ageels        #+#    #+#                 */
/*   Updated: 2022/10/03 22:16:52 by ageels        ########   odam.nl         */
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
// # include <sys/syslimits.h>
# include <stdlib.h>
# include <signal.h>
# include <stdbool.h>
# include <curses.h>
# include <term.h>

// Libft
# include "lib/libft/libft.h"

// Lexer
# include "src/lexer/lexer.h"

# define READ 0
# define WRITE 1

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
}	t_cmd;

// GLOBAL VAR
t_children	g_children;

// FILES & FUNCTIONS:
//prompt
char		*prompt(void);

//parser
int			parse(t_token *tokens, t_cmd *cmds);
int			set_bin(t_cmd *cmd, t_simple *simple);
t_simple	*new_simple(int argc, char **argv);
void		simple_add_back(t_simple **lst, t_simple *new_elem);
t_simple	*new_simple(int argc, char **argv);

//buildins (00)
void		bi_echo(void);
void		bi_cd(void);
void		bi_pwd(void);
void		bi_export(void);
void		bi_unset(void);
void		bi_env(void);
void		bi_exit(void);

//execute
int			execute(t_cmd cmds);

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


#endif
