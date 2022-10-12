#ifndef SUBSTITUTOR_H
# define SUBSTITUTOR_H

# include "../../minishell.h"

char	*get_envp_var(char *str, char **envp);
void	substitute_dquot(t_token *token, char **envp);

#endif