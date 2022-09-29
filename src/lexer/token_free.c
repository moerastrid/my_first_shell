#include "token.h"
#include <stdlib.h>

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
	while (token != NULL)
	{
		free_token(token);
		token = token->next;
	}
}
