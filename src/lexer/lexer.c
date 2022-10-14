/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: ageels <ageels@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/14 14:29:48 by ageels        #+#    #+#                 */
/*   Updated: 2022/10/14 14:35:59 by ageels        ########   odam.nl         */
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
	return (0);
}

static char	*get_data(int type, char *input)
{
	char	*data;

	if (type == WORD)
		data = ft_substr(input, 0, word_length(input));
	else if (type == QUOT)
		data = ft_substr(input, 1, quot_length(input));
	else if (type == DQUOT)
		data = ft_substr(input, 1, dquot_length(input));
	else if (type == DOLL)
		data = ft_substr(input, 1, word_length(input + 1));
	else if (type == DOLLQ)
		data = ft_substr(input, 0, 2);
	else
		data = NULL;
	return (data);
}

t_token	*tokenize(char *input)
{
	t_token	root;
	char	*data;
	int		type;
	t_token	*new;
	char	*end;

	end = input + ft_strlen(input);
	root.next = NULL;
	while (*input != '\0')
	{
		while (*input == ' ')
			input++;
		if (!*input)
			break ;
		type = token_type(input);
		data = get_data(type, input);
		new = token_new(data, type);
		token_add_back(&root, new);
		input += token_length(new);
		if (input > end)
		{
			print_tokens(root.next);
			free_token_list(root.next);
			return (NULL);
		}
	}
	merge_redirects(root.next);
	return (root.next);
}
