#ifndef ENV_H
# define ENV_H

# include "../../minishell.h"

char	*find_str(char *str, char **envp);
char	**copy_env(char **og);
int		env_replace(char *var_name, char *insert, char **envp);
char	**env_add(char *to_add, char **envp_ref);
char	**env_remove(char *var_name, char **envp);
int		count_envp(char **envp);
void	free_envc(char	**envc);

#endif