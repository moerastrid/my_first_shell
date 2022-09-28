/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer00.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnuyten <tnuyten@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 18:22:06 by tnuyten           #+#    #+#             */
/*   Updated: 2022/09/27 18:50:33 by tnuyten          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	is_token(char *str)
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

static int	token_type(char *str)
{
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

static int	token_length(t_token *token)
{
	int len;

	if (token->type == GREATGREAT || token->type == LESSLESS
		|| token->type == DOLLQ)
		len = 2;
	else if(token->type == WORD)
		len = ft_strlen(token->data);
	else
		len = 1;
	return (len);
}

static int word_length(char *input)
{
	int	len;

	len = 0;
	while(*input != ' ' && *input != '\0' && !is_token(input))
	{
		len++;
		input++;
	}
	return (len);
}

t_token *tokenize(char *input)
{
	t_token	root;
	char	*data;
	int		type;
	int		len;
	t_token *new;

	root.next = NULL;
	while (*input != '\0')
	{
		while(*input == ' ')
			input++;
		if(!*input)
			break;
		type = token_type(input);
		data = NULL;
		if (type == WORD)
			data = ft_substr(input, 0, word_length(input));
		new = token_new(data, type);
		token_add_back(&root, new);
		len = token_length(new);
		input += len;
	}
	return (root.next);
}

// Reference, old version without WORD type.
// char	*get_token_end(char *input, int type)
// {
// 	int	len;
//
// 	len = ft_strlen(input);
// 	if (len == 0)
// 		return (input);
// 	input++; //skip first symbol of token
// 	if (len > 1 && (type == GREATGREAT || type == LESSLESS)) //skip second symbol of token, if it exists.
// 		input++;
// 	while (*input)
// 	{
// 		if (is_token(input))
// 			return (input);
// 		input++;
// 	}
// 	return (input + ft_strlen(input));
// }
// t_token	*tokenize(char *input)
// {
// 	t_token	*token;
// 	char	*data;
// 	int		type;
//
// 	token = NULL;
// 	while (*input)
// 	{
// 		if (is_token(input))
// 		{
// 			type = token_type(input);
// 			data = ft_substr(input, 0, get_token_end(input, type) - input);
// 			printf("data: %s\n", data);
// 			if (token == NULL)
// 				token = token_new(data, type);
// 			else
// 				token_add_back(token, token_new(data, type));
// 			if (type == GREATGREAT || type == LESSLESS)
// 				input++;
// 		}
// 		input++;
// 	}
// 	return (token);
// }

// int main()
// {
// 	//t_token *tok = tokenize("alle tekst die hier staat wordt genegeerd! >>test >test <test <<test | test | test $");
//	t_token *tok = tokenize("echo string | hallo << test");

// 	while(tok != NULL)
// 	{
// 		printf("%d:[%s]\n", tok->type, tok->data);
// 		tok = tok->next;
// 	}
// }
