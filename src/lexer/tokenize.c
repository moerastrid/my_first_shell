/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tokenize.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: ageels <ageels@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/14 14:29:48 by ageels        #+#    #+#                 */
/*   Updated: 2022/10/24 22:26:13 by ageels        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"

static char	*get_data(int type, char *input)
{
	char	*data;

	data = NULL;
	if (type == WORD)
		data = ft_substr(input, 0, word_length(input));
	else if (type == QUOT)
		data = ft_substr(input, 1, quot_length(input));
	else if (type == DQUOT)
		data = ft_substr(input, 1, dquot_length(input));
	else if (type == DOLL)
		data = ft_substr(input, 1, doll_length(input + 1));
	else if (type == DOLLQ)
		data = ft_substr(input, 0, 2);
	else if (type == WSPACE)
		data = ft_substr(input, 0, 1);
	return (data);
}

// error values?
static int	check_token(t_token *token)
{
	int	type;

	type = token->type;
	if (token->data == NULL)
	{
		if (type == WORD)
		{
			g_errno = 10;
			return (10);
		}
	}
	return (0);
}

int	tokenize(t_cmd *cmd, char *input)
{
	int		type;
	t_token	*new;
	char	*end;

	end = input + ft_strlen(input);
	while (*input != '\0')
	{
		type = token_type(input);
		new = token_new(get_data(type, input), type);
		token_add_back(&(cmd->tokens), new);
		if (check_token(new) == -1)
			return (-1);
		input += token_length(new);
		if (input > end)
			return (-1);
	}
	return (0);
}
