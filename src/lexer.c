/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnuyten <tnuyten@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 18:22:06 by tnuyten           #+#    #+#             */
/*   Updated: 2022/09/26 21:57:30 by tnuyten          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "token.c"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	int		i;
	char	*ptr;

	if (!s)
		return (NULL);
	ptr = malloc(len + 1);
	if (!ptr)
		return (NULL);
	while (start-- && *s)
		s++;
	i = 0;
	while (*s && len > 0)
	{
		ptr[i] = *s++;
		len--;
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}


static int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned char	c1;
	unsigned char	c2;

	while (n > 0)
	{
		n--;
		c1 = (unsigned char) *s1++;
		c2 = (unsigned char) *s2++;
		if (c1 != c2)
			return (c1 - c2);
		if (c1 == '\0')
			return (0);
	}
	return (0);
}

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

int main()
{
	t_token *tt = tokenize("cat <test.txt | ls -la > output.txt << test EOF >>output.txt | echo $??");

	while(tt != NULL)
	{
		printf("%d: %s\n", tt->type, tt->data);
		tt = tt->next;
	}
}