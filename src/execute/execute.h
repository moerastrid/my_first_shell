/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute.h                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: ageels <ageels@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/30 00:43:26 by ageels        #+#    #+#                 */
/*   Updated: 2022/10/06 18:00:09 by ageels        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_H
# define EXECUTE_H

# include "../../minishell.h"

void	exec_cmd(t_simple simple);
int		family_life(t_cmd cmds);
int		pickup_kids(void);
pid_t	child(t_cmd cmds, int *write_pipe, int *read_pipe, int cmd_no);
int		only_child(t_cmd cmds);

#endif