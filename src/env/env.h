#ifndef ENV_H
# define ENV_H

#include "../../minishell.h"

char	**copy_env(char **og);
char	**env_add(char *to_add, char **envp);
char	**env_remove(char *var_name, char **envp);
int		count_envp(char **envp);
void	free_envc(char	**envc);

#endif