#include "token.h"

void	free_token(t_token *token)
{
	if (token == NULL)
		return ;
	if (token->data != NULL)
		free(token->data);
	free(token);
}

void	free_token_list(t_token *token)
{
	t_token	*temp;
	while (token != NULL)
	{
		temp = token->next;
		free_token(token);
		token = temp;
	}
}
