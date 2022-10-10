#include "../../minishell.h"

static char* get_envp_var(char *str, char **envp)
{
	int		i;
	char	*env_head;
	int		env_head_len;
	int		comp;

	i = 0;
	while (envp && envp[i])
	{
		env_head = ft_substr(envp[i], 0, ft_strchr(envp[i], '=') - envp[i]);
		env_head_len = ft_strlen(env_head);
		comp = ft_strncmp(str, env_head, env_head_len);
		free(env_head);
		if (comp == 0)
			return &envp[i][env_head_len + 1];
		i++;
	}
	return (NULL);
}

void	substitute(t_token *tokens, char **envp)
{
	char	*sub;

	while (tokens)
	{
		if (tokens->type == DOLL)
		{
			if (tokens->data == NULL)
				return ;
			sub = get_envp_var(tokens->data, envp);
			free(tokens->data);
			if (sub == NULL) // Var not found
			{
				tokens->data = ft_strdup("");
				return ;
			}
			tokens->data = ft_strdup(sub);
		}
		if (tokens->type == DOLLQ)
		{
			;
		}
		tokens = tokens->next;
	}
}
