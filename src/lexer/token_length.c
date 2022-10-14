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

// GREATGREAT, LESSLESS and DOLLQ have a fixed length of two.
// WORD has length of the strlen of its data
// QUOT and DQUOT have strlen(data) + 2 length, the quotes are skipped.
// DOLL has length strlen(data) + 1, the dollar is skipped.
// All other types have length 1.

int	token_length(t_token *token)
{
	int	len;
	int	type;

	type = token->type;
	if (type == GREATGREAT || type == LESSLESS || type == DOLLQ)
		len = 2;
	else if (type == WORD || type == QUOT || type == DQUOT || type == DOLL)
		len = ft_strlen(token->data);
	else
		len = 1;
	if (type == QUOT || type == DQUOT)
		len += 2;
	if (type == DOLL)
		len ++;
	return (len);
}

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
