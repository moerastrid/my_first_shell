/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute.h                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: ageels <ageels@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/30 00:43:26 by ageels        #+#    #+#                 */
/*   Updated: 2022/11/03 15:27:13 by ageels        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_H
# define EXECUTE_H

# include "./builtins/builtins.h"

typedef struct s_children {
	pid_t				id;
	struct s_children	*next;
}	t_children;

# define READ 0
# define WRITE 1

//errno:
void		catch_errno(int err);

//family_life.c
int			family_life(t_cmd *cmds);

//children.c
void		child(t_cmd *cmd, int *writep, int *readp, int cmd_no);

//redirect.c
int			redirect_infile(t_str_list *infiles);
int			redirect_outfile(t_str_list *outfiles);
int			infile_check_access(t_str_list *infiles);

//single.c
void		exec_cmd(t_simple *simple, char **envp);
int			only_child(t_cmd *cmds);
int			signal_catcher(pid_t child_pid);

//call_builtin.c
int			is_builtin(t_simple *simple);
int			exec_builtin(t_simple *t, t_cmd *cmd);

//touch_children.c
t_children	*new_child(pid_t id);
void		child_add_back(t_children **root, t_children *new);

#endif