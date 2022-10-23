/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   token_free.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: ageels <ageels@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/14 14:29:24 by ageels        #+#    #+#                 */
/*   Updated: 2022/10/14 14:29:25 by ageels        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"

void	free_token(t_token *token)
{
	if (token == NULL)
		return ;
	if (token->data != NULL)
	{
		free(token->data);
		token->data = NULL;
	}
	free(token);
	token = NULL;
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
