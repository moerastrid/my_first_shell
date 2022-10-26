/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   substitutor.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: ageels <ageels@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/21 22:30:44 by ageels        #+#    #+#                 */
/*   Updated: 2022/10/24 21:32:08 by ageels        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "substitutor.h"

char	*get_envp_var(char *str, char **envp)
{
	int		i;
	char	*end;

	i = 0;
	while (envp && envp[i])
	{
		end = ft_strchr(envp[i], '=');
		if (end == NULL)
			continue ;
		if (ft_strlen(envp[i]) > ft_strlen(str)
			&& !ft_strncmp(str, envp[i], ft_strlen(str))
			&& envp[i][ft_strlen(str)] == '=')
			return (ft_strdup(&(envp[i][end - envp[i] + 1])));
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
		if (ft_strlen(token->data) == 0)
			sub = ft_strdup("$");
		else
			sub = get_envp_var(token->data, envp);
		free(token->data);
		if (sub == NULL)
		{
			token->data = ft_strdup("");
			return ;
		}
		token->data = sub;
	}
	if (ft_strchr(token->data, ' ') || ft_strchr(token->data, '\t') \
	|| ft_strchr(token->data, '\n'))
		split_token(token);
}

static void	substitute_dollq(t_token **tokens)
{
	if ((*tokens)->data)
		free((*tokens)->data);
	(*tokens)->data = ft_itoa(g_errno);
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
			substitute_dollq(&tokens);
		if (tokens->type == DQUOT)
			substitute_dquot(tokens, envp);
		tokens = tokens->next;
	}
	merge_words(cmd.tokens);
	token_delete_empty_subs(&cmd.tokens);
}
