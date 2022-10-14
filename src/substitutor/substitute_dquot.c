#include "substitutor.h"

static char	*get_word(char *input)
{
	char	*var_end;

	var_end = ft_strchr(input, ' ');
	if (var_end == NULL)
		var_end = ft_strchr(input, '\0');
	else
		var_end -= 1;
	return (ft_substr(input, 1, var_end - input));
}

static char	*replace_once(char *input, char *full_input,
		int *pre_sub_len, char **envp)
{
	char	*var_name;
	char	*sub;
	char	*pre;
	char	*post;
	char	*post_begin;

	var_name = get_word(input);
	if (var_name == NULL)
		return (NULL);
	if (ft_strlen(var_name) == 0)
	{
		free(var_name);
		return (ft_strdup(full_input));
	}
	sub = get_envp_var(var_name, envp);
	if (sub == NULL)
		sub = ft_strdup("");
	pre = ft_substr(full_input, 0, input - full_input);
	post_begin = input + ft_strlen(var_name) + 1;
	post = ft_substr(post_begin, 0, ft_strlen(post_begin) + 1);
	*pre_sub_len = ft_strlen(pre) + ft_strlen(sub);
	free(var_name);
	return (ft_strjoin3_free(pre, sub, post));
}

void	substitute_dquot(t_token *token, char **envp)
{
	char	*input;
	char	*new_data;
	int		pre_sub_len;

	input = token->data;
	while (input && *input != '\0')
	{
		while (*input != '$' && *input != '\0')
			input++;
		if (!*input)
			break ;
		new_data = replace_once(input, token->data, &pre_sub_len, envp);
		free(token->data);
		token->data = new_data;
		input = token->data + pre_sub_len;
	}
	if (input == NULL)
		printf("%s\n", "Substitution error");
}