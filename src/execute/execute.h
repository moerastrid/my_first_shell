/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute.h                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: ageels <ageels@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/30 00:43:26 by ageels        #+#    #+#                 */
/*   Updated: 2022/10/10 14:28:57 by ageels        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_H
# define EXECUTE_H

# include "../../minishell.h"

int			family_life(t_cmd cmds);
int			pickup_kids(void);
pid_t		child(t_cmd cmds, int *write_pipe, int *read_pipe, int cmd_no);
void		exec_cmd(t_simple simple);
int			only_child(t_cmd cmds);
void		redirect_infile(t_str_list *infiles);
void		redirect_outfile(t_str_list *outfiles);

#endif