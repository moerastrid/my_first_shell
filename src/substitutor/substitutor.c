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
		comp = ft_strlen(str) && ft_strncmp(str, env_head, ft_strlen(str)) == 0;
		free(env_head);
		if (comp == 1)
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
	token->data = ft_itoa(g_errno);
}

void	substitute(t_cmd cmd, char **envp)
{
	t_token	*tokens;

	tokens = cmd.tokens;
	while (tokens)
	{
		if (tokens->type == DOLL)
			substitute_doll(tokens, envp);
		if (tokens->type == DOLLQ)
			substitute_dollq(tokens);
		if (tokens->type == DQUOT)
			substitute_dquot(tokens, envp);
		tokens = tokens->next;
	}
	merge_words(cmd.tokens);
}
