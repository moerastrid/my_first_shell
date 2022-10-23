/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   setup.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: ageels <ageels@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/21 22:30:21 by ageels        #+#    #+#                 */
/*   Updated: 2022/10/21 22:30:22 by ageels        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef SETUP_H
# define SETUP_H

# include "../../minishell.h"
# include "../env/env.h"
# include "../heredoc/heredoc.h"

char		**getpaths(char **envp);
int			setup(t_cmd *cmd, char **envp, int argc);
void		reset(t_cmd *cmd, char *line);
void		clear_cmd(t_cmd *cmd);

#endif