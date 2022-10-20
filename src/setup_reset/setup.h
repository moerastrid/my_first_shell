#ifndef SETUP_H
# define SETUP_H

# include "../../minishell.h"
# include "../env/env.h"

char		**getpaths(char **envp);
int			setup(t_cmd *cmd, char **envp, int argc);
void		reset(t_cmd *cmd, char *line);
void		clear_cmd(t_cmd *cmd);

#endif