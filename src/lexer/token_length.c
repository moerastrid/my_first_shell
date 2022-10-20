/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   token_length.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: ageels <ageels@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/14 14:30:28 by ageels        #+#    #+#                 */
/*   Updated: 2022/10/14 15:42:50 by ageels        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"

int	word_length(char *input)
{
	int	len;

	len = 0;
	while (*input != ' ' && *input != '\0' && !is_token_char(input))
	{
		len++;
		input++;
	}
	return (len);
}

int	quot_length(char *input)
{
	int	count;
	int	type;

	type = token_type(input);
	count = 0;
	input++;
	while (*input != '\0' && token_type(input) != type)
	{
		count++;
		input++;
	}
	return (count);
}

int	dquot_length(char *input)
{
	int	count;
	int	type;

	type = token_type(input);
	count = 0;
	input++;
	while (*input != '\0' && token_type(input) != type)
	{
		count++;
		input++;
	}
	return (count);
}

int	doll_length(char *input)
{
	int	len;

	len = 0;
	while (ft_isalnum(*input) || *input == '_')
	{
		len++;
		input++;
	}
	return (len);
}

int	redir_length(char *input)
{
	int	len;

	len = 0;
	while (*input == ' ')
	{
		input++;
		len++;
	}
	return (len + word_length(input));
}
