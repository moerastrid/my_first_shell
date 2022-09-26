#include "../minishell.h"

void token_add_back(t_token* tokens, t_token* new)
{
	if(tokens == NULL)
		return ;
	while(tokens->next != NULL)
	{
		tokens = tokens->next;
	}
	tokens->next = new;
}

t_token* token_new(char *data, int type)
{
	t_token *token;

	token = ft_calloc(1, sizeof(t_token));
	if (token == NULL)
		return (NULL);
	token->data = data;
	token->type = type;
	token->next = NULL;
	return (token);
}