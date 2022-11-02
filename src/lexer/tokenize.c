/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tokenize.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: ageels <ageels@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/14 14:29:48 by ageels        #+#    #+#                 */
/*   Updated: 2022/11/02 15:22:41 by ageels        ########   odam.nl         */
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
		data = ft_substr(input, 1, quot_length(input));
	else if (type == DOLL)
		data = ft_substr(input, 1, doll_length(input + 1));
	else if (type == DOLLQ)
		data = ft_substr(input, 0, 2);
	else if (type == WSPACE)
		data = ft_substr(input, 0, 1);
	return (data);
}

static int	print_quot_error(int type, int err)
{
	char	*str;

	if (type == QUOT)
		str = "'";
	else if (type == DQUOT)
		str = "\"";
	else
		return (-1);
	ft_putstr_fd("minishell: syntax error: unmatched '", STDERR_FILENO);
	ft_putstr_fd(str, STDERR_FILENO);
	ft_putstr_fd("'\n", STDERR_FILENO);
	return (err);
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
		if (new == NULL)
		{
			cmd->err = 10;
			return (-1);
		}
		token_add_back(&(cmd->tokens), new);
		input += token_length(new);
		if (input > end)
			return (print_quot_error(type, -1));
	}
	return (0);
}
