/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: ageels <ageels@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/14 14:29:48 by ageels        #+#    #+#                 */
/*   Updated: 2022/10/21 18:50:49 by ageels        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"

int	is_token_char(char *str)
{
	if (ft_strncmp(str, "$", 1) == 0)
		return (1);
	if (ft_strncmp(str, "|", 1) == 0)
		return (1);
	if (ft_strncmp(str, ">", 1) == 0)
		return (1);
	if (ft_strncmp(str, "<", 1) == 0)
		return (1);
	if (ft_strncmp(str, "\"", 1) == 0)
		return (1);
	if (ft_strncmp(str, "'", 1) == 0)
		return (1);
	return (0);
}

int	token_type(char *str)
{
	if (ft_strncmp(str, "'", 1) == 0)
		return (QUOT);
	if (ft_strncmp(str, "\"", 1) == 0)
		return (DQUOT);
	if (ft_strncmp(str, "$?", 2) == 0)
		return (DOLLQ);
	if (ft_strncmp(str, "$", 1) == 0)
		return (DOLL);
	if (ft_strncmp(str, "|", 1) == 0)
		return (PIPE);
	if (ft_strncmp(str, ">>", 2) == 0)
		return (GREATGREAT);
	if (ft_strncmp(str, "<<", 2) == 0)
		return (LESSLESS);
	if (ft_strncmp(str, ">", 1) == 0)
		return (GREAT);
	if (ft_strncmp(str, "<", 1) == 0)
		return (LESS);
	if (ft_strncmp(str, " ", 1) == 0)
		return (WSPACE);
	if (ft_strncmp(str, "\t", 1) == 0)
		return (WSPACE);
	if (ft_strncmp(str, "\n", 1) == 0)
		return (WSPACE);
	return (WORD);
}

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
	// else if (type == LESSLESS)
	// 	data = ft_substr(input, 2, lessless_length(input + 2));
	// else if (type == GREAT || type == LESS)
	// 	data = ft_substr(input, 1, redir_length(input + 1));
	// else if (type == GREATGREAT)
	// 	data = ft_substr(input, 2, redir_length(input + 2));
	else if (type == WSPACE)
		data = ft_substr(input, 0, 1);
	return (data);
}

int	token_length(t_token *token)
{
	int	len;
	int	type;

	type = token->type;
	len = 1;
	if (type & (WORD + QUOT + DQUOT + DOLL))
		len = ft_strlen(token->data);
	if (type & (QUOT + DQUOT))
		len += 2;
	if (type & (DOLL + DOLLQ + GREATGREAT + LESSLESS))
		len += 1;
	return (len);
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
			return (-1);
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
		{
			printf("%s\n", "check token error");
			return (-1);
		}
		input += token_length(new);
		if (input > end)
		{
			print_tokens(cmd->tokens);
			printf("%s\n", "past end error");
			return (-1);
		}
	}
	return (0);
}
