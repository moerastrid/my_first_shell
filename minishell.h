/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: ageels <ageels@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/27 22:19:40 by ageels        #+#    #+#                 */
/*   Updated: 2022/10/26 19:11:46 by ageels        ########   odam.nl         */
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

// parser
int			parse(t_cmd *cmds);

// substitutor
void		substitute(t_cmd cmd, char **envp);

//utils
char		**single_split(char const *s, char c);

//heredoc
int			heredoc(t_cmd *cmd, char **retstr);

#endif