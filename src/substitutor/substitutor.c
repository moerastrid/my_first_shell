#include "../../minishell.h"

static char* get_envp_var(char *str, char **envp)
{
	int		i;
	char	*env_head;
	int		comp;

	i = 0;
	while (envp && envp[i])
	{
		env_head = ft_substr(envp[i], 0, ft_strchr(envp[i], '=') - envp[i]);
		comp = ft_strncmp(str, env_head, ft_strlen(env_head));
		free(env_head);
		if (comp == 0)
		{

			return envp[i];
		}
		i++;
	}
	return (NULL);
}

void	substitute(t_token *tokens, char **envp)
{
	char *sub;
	t_token *token;

	token = tokens;
	while (token)
	{
		if (token->type == DOLL)
			if (token->data == NULL)
				return ;
			sub = get_envp_var(token->data, envp);
			printf("%s\n", sub);
			if (sub == NULL)
				// Var not found
			free(token->data);
			token->data = sub;
		if (token->type == DOLLQ)
			;
		token = token->next;
	}
}
