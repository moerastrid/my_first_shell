/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtins.h                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: ageels <ageels@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/14 14:06:36 by ageels        #+#    #+#                 */
/*   Updated: 2022/10/21 21:49:17 by ageels        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "../../../minishell.h"
# include "../../env/env.h"

int			bi_echo(t_simple *simple);
int			bi_cd(t_simple *simple, t_cmd *cmd);
int			bi_pwd(void);
int			bi_export(t_simple simple, t_cmd *cmd);
int			bi_unset(t_simple simple, t_cmd *cmd);
int			bi_env(t_cmd *cmd);
void		bi_exit(t_cmd *cmd, t_simple *simple);

#endif