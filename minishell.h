/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: ageels <ageels@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/27 22:19:40 by ageels        #+#    #+#                 */
/*   Updated: 2022/10/03 18:01:42 by ageels        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>
# include <sys/stat.h>
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

pid_t	*g_children;

//STRUCTS:
typedef struct s_simple {
	char			**argv;
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

// FILES & FUNCTIONS:
//prompt
char		*prompt(void);

//parser
int			parse(t_token *tokens, t_cmd *cmds);
int			generate_simple_command(t_cmd *cmd, char **argv);

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

//DEBUG #TODO REMOVE... ILLEGAL FUNCTION!
void		print_token_type(enum e_token_type num);
void		print_str_list(t_str_list *root, int mode);
void		print_tokens(t_token *root);

#endif
