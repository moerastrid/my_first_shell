#include "substitutor.h"

char	*get_envp_var(char *str, char **envp)
{
	int		i;
	char	*env_head;
	int		env_head_len;
	int		comp;
	char	*end;

	i = 0;
	while (envp && envp[i])
	{
		end = ft_strchr(envp[i], '=');
		if (end == NULL)
			return (NULL);
		env_head = ft_substr(envp[i], 0, end - envp[i]);
		env_head_len = ft_strlen(env_head);
		comp = ft_strncmp(str, env_head, ft_strlen(str));
		free(env_head);
		if (comp == 0)
			return (ft_strdup(&(envp[i][env_head_len + 1])));
		i++;
	}
	return (NULL);
}

static void	substitute_doll(t_token *token, char **envp)
{
	char	*sub;

	if (token->type == DOLL)
	{
		if (token->data == NULL)
			return ;
		sub = get_envp_var(token->data, envp);
		free(token->data);
		if (sub == NULL)
		{
			token->data = ft_strdup("");
			return ;
		}
		token->data = sub;
	}
}

static void	substitute_dollq(t_token *token)
{
	;
}

void	substitute(t_token *tokens, char **envp)
{
	t_token	*token;

	token = tokens;
	while (token)
	{
		if (token->type == DOLL)
		{
			substitute_doll(token, envp);
		}
		if (token->type == DOLLQ)
		{
			substitute_dollq(token);
		}
		if (token->type == DQUOT)
		{
			substitute_dquot(token, envp);
		}
		token = token->next;
	}
}
