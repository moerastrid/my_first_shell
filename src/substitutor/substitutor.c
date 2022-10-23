/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   substitutor.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: ageels <ageels@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/21 22:30:44 by ageels        #+#    #+#                 */
/*   Updated: 2022/10/21 23:10:17 by ageels        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "substitutor.h"

char	*get_envp_var(char *str, char **envp)
{
	int		i;
	char	*env_head;
	size_t	env_head_len;
	int		comp;
	char	*end;

	i = 0;
	while (envp && envp[i])
	{
		end = ft_strchr(envp[i], '=');
		if (end == NULL)
			continue;
		env_head = ft_substr(envp[i], 0, end - envp[i]);
		env_head_len = ft_strlen(env_head);
		if(env_head_len == ft_strlen(str))
		{
			comp = ft_strncmp(str, env_head, ft_strlen(env_head)) == 0;
			if (comp == 1)
			{
				free(env_head);
				return (ft_strdup(&(envp[i][env_head_len + 1])));
			}
		}
		free(env_head);
		i++;
	}
	return (NULL);
}

static void	split_token(t_token *token)
{
	char	**splitted;
	char	**s;
	t_token	*old_next;

	splitted = ft_split_multiple(token->data, " \t\n");
	if (splitted == NULL)
		return ;
	s = splitted;
	free(token->data);
	token->data = *s++;
	old_next = token->next;
	while (s && *s)
	{
		token->next = token_new(ft_strdup(" "), WSPACE);
		token = token->next;
		token->next = token_new(ft_strdup(*s), WORD);
		token = token->next;
		free(*s++);
	}
	token->next = old_next;
	free(splitted);
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
	if(ft_strchr(token->data, ' ') || ft_strchr(token->data, '\t')\
	|| ft_strchr(token->data, '\n'))
		split_token(token);
}

void	substitute(t_cmd cmd, char **envp)
{
	t_token	*tokens;
	t_doc	*doc;

	doc = cmd.doc;
	tokens = cmd.tokens;
	while (tokens)
	{
		if (tokens->type == DOLL)
			substitute_doll(tokens, envp);
		if (tokens->type == DOLLQ)
			tokens->data = ft_itoa(g_errno);
		if (tokens->type == DQUOT)
			substitute_dquot(tokens, envp);
		if (tokens->type == LESSLESS)
		{
			if(check_heredoc_for_substitution(doc))
			{
				substitute_heredoc(&doc, envp);
				tokens->data = ft_strjoin(doc->name, "_42cpy");
			}
			doc = doc->next;
		}
		tokens = tokens->next;
	}
	merge_words(cmd.tokens);
}
