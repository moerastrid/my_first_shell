#include "token.h"

static int	is_token_char(char *str)
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

// GREATGREAT, LESSLESS and DOLLQ have a fixed length of two.
// WORD has length of the strlen of its data
// QUOT and DQUOT have strlen(data) + 2 length, the quotes are skipped.
// DOLL has length strlen(data) + 1, the dollar is skipped.
// All other types have length 1.
static int	token_length(t_token *token)
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

static int	word_length(char *input)
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

static int	quot_length(char *input)
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

static int	dquot_length(char *input)
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

char *get_data(int type, char *input)
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
