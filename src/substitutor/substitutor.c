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

static int	count_split(char **arr)
{
	int	count;

	count = 0;
	while (arr && *arr)
	{
		count ++;
		arr++;
	}
	return (count);
}

static void	split_token(t_token *token)
{
	char	**splitted;
	int		num_strings;
	int		i;
	t_token	*old_next;
	t_token	*iter;

	splitted = ft_split_multiple(token->data, " \t\n");
	if (splitted == NULL)
		return ;
	num_strings = count_split(splitted);
	if (num_strings >= 1)
		token->data = splitted[0];
	if (num_strings > 1)
		old_next = token->next;
	i = 1;
	iter = token;
	while (i < num_strings)
	{
		iter->next = token_new(splitted[i], token->type);
		iter = iter->next;
	}
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
	split_token(token);
}

//static void	substitute_dollq(t_token *token)
//{
//	token->data = ft_itoa(g_errno);
//}

void	substitute(t_cmd cmd, char **envp)
{
	t_token	*tokens;

	tokens = cmd.tokens;
	while (tokens)
	{
		if (tokens->type == DOLL)
			substitute_doll(tokens, envp);
		if (tokens->type == DOLLQ)
			tokens->data = ft_itoa(g_errno);
		if (tokens->type == DQUOT)
			substitute_dquot(tokens, envp);
		tokens = tokens->next;
	}
	merge_words(cmd.tokens);
}
