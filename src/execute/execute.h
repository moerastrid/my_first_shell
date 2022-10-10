/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute.h                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: ageels <ageels@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/30 00:43:26 by ageels        #+#    #+#                 */
/*   Updated: 2022/10/10 23:44:28 by ageels        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_H
# define EXECUTE_H

# include "../../minishell.h"

# define READ 0
# define WRITE 1

int			family_life(t_cmd cmds);
int			pickup_kids(void);
pid_t		child(t_cmd cmds, int *write_pipe, int *read_pipe, int cmd_no);
void		exec_cmd(t_simple *simple, char **envp);
int			only_child(t_cmd cmds);
void		redirect_infile(t_str_list *infiles);
void		redirect_outfile(t_str_list *outfiles);
int			is_buildin(t_simple	*simple);
void		exec_buildin(t_simple *t, t_cmd cmd, t_token *tokens);

#endif