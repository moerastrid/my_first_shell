/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: ageels <ageels@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/27 22:19:40 by ageels        #+#    #+#                 */
/*   Updated: 2022/10/21 19:02:17 by ageels        ########   odam.nl         */
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

# include "structs.h"
# include "lib/libft/libft.h"
# include "src/display/display.h"
# include "src/lexer/token.h"
# include "src/setup_reset/setup.h"
// #remove before handin
# include "src/debug/debug.h"

// GLOBAL VAR
int	g_errno;

// FILES & FUNCTIONS:
//display
char		*prompt(t_cmd	*cmd);

// execute
int			execute(t_cmd *cmds);

// lexer
int			tokenize(t_cmd *cmd, char *input);
void		free_token_list(t_token *token);

// parser
void		free_str_list(t_str_list *root);
void		free_simples(t_simple *simples);
int			parse(t_cmd *cmds);
void		cmd_simples_set_bin(t_cmd *cmd);

// substitutor
void		substitute(t_cmd cmd, char **envp);
void		redirect_outfile(t_str_list *outfiles);

//utils
char		**single_split(char const *s, char c);

//heredoc
int			heredoc(t_cmd *cmd, char **retstr);

#endif