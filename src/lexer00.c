/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer00.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnuyten <tnuyten@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 18:22:06 by tnuyten           #+#    #+#             */
/*   Updated: 2022/09/26 21:59:16 by tnuyten          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int is_token(char *str)
{
	if(ft_strncmp(str, "$", 1) == 0)
		return 1;
	if(ft_strncmp(str, "|", 1) == 0)
		return 1;
	if(ft_strncmp(str, ">", 1) == 0)
		return 1;
	if(ft_strncmp(str, "<", 1) == 0)
		return 1;
	return (0);
}

static int get_token_type(char *str)
{
	if(ft_strncmp(str, "$?", 2) == 0)
		return DOLLQ;
	if(ft_strncmp(str, "$", 1) == 0)
		return DOLL;
	if(ft_strncmp(str, "|", 1) == 0)
		return PIPE;
	if(ft_strncmp(str, ">>", 2) == 0)
		return GREATGREAT;
	if(ft_strncmp(str, "<<", 2) == 0)
		return LESSLESS;
	if(ft_strncmp(str, ">", 1) == 0)
		return GREAT;
	if(ft_strncmp(str, "<", 1) == 0)
		return LESS;
	return (0);
}

char	*get_data_end(char *input, int type)
{
	int len;

	printf("%d: %s\n", type, input);

	len = ft_strlen(input);
	if(len == 0)
		return input;
	input++; //skip first symbol of token
	if (len >= 2 && (type == GREATGREAT || type == LESSLESS))
	{
		input++;
	}
	while (*input)
	{
		if (is_token(input))
			return (input);
		input++;
	}
	return (input + ft_strlen(input) - 1);
}

t_token	*tokenize(char *input)
{
	t_token	*token;
	int		type;
	char	*data;

	token = NULL;
	while (*input)
	{
		if (is_token(input))
		{
			type = get_token_type(input);
			printf("%lu\n", get_data_end(input, type) - input);
			data = ft_substr(input, 0, get_data_end(input, type) - input);
			if (token == NULL)
				token = token_new(data, type);
			else
				token_add_back(token, token_new(data, type));
			if(type == GREATGREAT || type == LESSLESS)
				input++;
		}
		input++;
	}
	return (token);
}
