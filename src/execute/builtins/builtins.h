/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtins.h                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: ageels <ageels@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/14 14:06:36 by ageels        #+#    #+#                 */
/*   Updated: 2022/10/14 14:08:32 by ageels        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

int			bi_echo(t_simple *simple);
int			bi_cd(void);
int			bi_pwd(t_cmd cmd);
int			bi_export(void);
int			bi_unset(void);
int			bi_env(t_cmd cmd);
void		bi_exit(t_cmd cmd, t_token *tokens);

#endif