/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: ageels <ageels@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/27 22:19:40 by ageels        #+#    #+#                 */
/*   Updated: 2022/10/31 23:32:40 by ageels        ########   odam.nl         */
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

// GLOBAL VAR
int	g_errno;

// FILES & FUNCTIONS:
//display
char		*prompt(t_cmd	*cmd);

// execute
int			execute(t_cmd *cmds);

//heredoc
int			heredoc(t_cmd *cmd, char **retstr);

// lexer
int			tokenize(t_cmd *cmd, char *input);

// parser
int			parse(t_cmd *cmds);

// substitutor
void		substitute(t_cmd *cmd, char **envp);

#endif