#ifndef EXECUTE_H
# define EXECUTE_H

# include "../../minishell.h"

void	exec_cmd(t_simple simple);
int		family_life(t_cmd cmds);
int		parent(int *children, t_cmd cmds, int *pfd);
int		child(t_cmd cmds, int *write_pipe, int *read_pipe, int cmd_no);
int		single_parent(t_cmd cmds);

#endif