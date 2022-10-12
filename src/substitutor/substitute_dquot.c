#include "substitutor.h"

static void	free_four(char *s1, char *s2, char *s3, char *s4)
{
	if (s1)
		free(s1);
	if (s2)
		free(s2);
	if (s3)
		free(s3);
	if (s4)
		free(s4);
	s1 = NULL;
	s2 = NULL;
	s3 = NULL;
	s4 = NULL;
}

static char	*ft_strjoin3_free(char *s1, char *s2, char *s3)
{
	char	*tmp;
	char	*ret;

	if (!s1 || !s2 || !s3)
		return (NULL);
	tmp = ft_strjoin(s1, s2);
	if (tmp == NULL)
		return (NULL);
	ret = ft_strjoin(tmp, s3);
	free_four(s1, s2, s3, tmp);
	return (ret);
}

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
			break;
		new_data = replace_once(input, token->data, &pre_sub_len, envp);
		free(token->data);
		token->data = new_data;
		input = token->data + pre_sub_len;
	}
	if (input == NULL)
		printf("%s\n", "Substitution error");
}