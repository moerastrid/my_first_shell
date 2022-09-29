#include "../../minishell.h"

static int	is_token(char *str)
{
	if (ft_strncmp(str, "'", 1) == 0)
		return (1);
	if (ft_strncmp(str, "\"", 1) == 0)
		return (1);
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

static int	word_length(char *input)
{
	int	len;

	len = 0;
	while (*input != ' ' && *input != '\0' && !is_token(input))
	{
		len++;
		input++;
	}
	return (len);
}

static void	merge_redirects(t_token *token)
{
	int		type;

	while (token != NULL)
	{
		type = token->type;
		if (type == LESS || type == GREAT || type == LESSLESS
			|| type == GREATGREAT)
		{
			merge_token_with_next(token);
		}
		token = token->next;
	}
}

t_token	*tokenize(char *input)
{
	t_token	root;
	char	*data;
	int		type;
	int		len;
	t_token	*new;

	root.next = NULL;
	while (*input != '\0')
	{
		while (*input == ' ')
			input++;
		if (!*input)
			break ;
		type = token_type(input);
		data = NULL;
		if (type == WORD)
			data = ft_substr(input, 0, word_length(input));
		new = token_new(data, type);
		token_add_back(&root, new);
		len = token_length(new);
		input += len;
	}
	merge_redirects(root.next);
	return (root.next);
}
