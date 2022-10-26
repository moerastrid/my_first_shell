/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   substitute_dquot.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: ageels <ageels@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/21 22:30:36 by ageels        #+#    #+#                 */
/*   Updated: 2022/10/24 21:32:14 by ageels        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "substitutor.h"

static int	is_word_char(char c)
{
	if (ft_isalnum(c) || c == '_')
		return (1);
	return (0);
}

static char	*get_word(char *input)
{
	char	*var_end;

	if (ft_strlen(input) <= 1)
		return (NULL);
	var_end = input + 1;
	if (ft_isdigit(*var_end))
		return (ft_substr(input, 1, 1));
	while (is_word_char(*var_end))
		var_end++;
	return (ft_substr(input, 1, var_end - 1 - input));
}

char	*rep_once(char *input, char *full_input, int *presublen, char **envp)
{
	char	*var_name;
	char	*sub;
	char	*pre;
	char	*post;
	char	*post_begin;

	var_name = get_word(input);
	if (var_name == NULL)
		return (NULL);
	if (ft_strlen(var_name) == 0)
	{
		free(var_name);
		return (ft_strdup(full_input));
	}
	sub = get_envp_var(var_name, envp);
	if (sub == NULL)
		sub = ft_strdup("");
	pre = ft_substr(full_input, 0, input - full_input);
	post_begin = input + ft_strlen(var_name) + 1;
	post = ft_substr(post_begin, 0, ft_strlen(post_begin) + 1);
	*presublen = ft_strlen(pre) + ft_strlen(sub);
	free(var_name);
	return (ft_strjoin3_free(pre, sub, post));
}

void	substitute_dquot(t_token *token, char **envp)
{
	char	*input;
	char	*new_data;
	int		presublen;

	input = token->data;
	presublen = 0;
	while (input && *input != '\0')
	{
		while (*input != '$' && *input != '\0')
			input++;
		if (!*input || !*(input + 1))
			break ;
		if (is_word_char(*(input + 1)) == 0)
		{
			input++;
			continue ;
		}
		new_data = rep_once(input, token->data, &presublen, envp);
		if(new_data == NULL)
			return ;
		free(token->data);
		token->data = new_data;
		input = token->data + presublen;
	}
}
