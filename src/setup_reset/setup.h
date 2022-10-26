/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   setup.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: ageels <ageels@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/21 22:30:21 by ageels        #+#    #+#                 */
/*   Updated: 2022/10/26 19:16:40 by ageels        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef SETUP_H
# define SETUP_H

# include "../../minishell.h"
# include "../env/env.h"
# include "../heredoc/heredoc.h"
# include "../parser/parser.h"
# include "../lexer/token.h"

char		**getpaths(char **envp);
int			setup(t_cmd *cmd, char **envp);
void		reset(t_cmd *cmd, char *line);
void		clear_cmd(t_cmd *cmd);
void		unlink_docs(t_doc *docs);
int			check_c_mode(int argc, char **argv, char **input);

#endif