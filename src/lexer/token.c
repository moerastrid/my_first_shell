/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   token.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: ageels <ageels@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/14 14:29:43 by ageels        #+#    #+#                 */
/*   Updated: 2022/10/14 14:29:44 by ageels        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"

void	token_add_back(t_token **root, t_token *new)
{
	t_token *node;

	if (!root)
		return ;
	node = root[0];
	if (node != NULL)
	{
		while (node->next != NULL)
		node = node->next;
		node->next = new;
	}
	else
		*root = new;
}

t_token	*token_new(char *data, int type)
{
	t_token	*token;

	token = ft_calloc(1, sizeof(t_token));
	if (token == NULL)
		return (NULL);
	token->data = data;
	token->type = type;
	token->next = NULL;
	return (token);
}

void	merge_token_with_next(t_token *token)
{
	t_token	*temp;

	if (token->next == NULL)
		return ;
	token->data = token->next->data;
	temp = token->next;
	token->next = token->next->next;
	free(temp);
}

void	merge_redirects(t_token *token)
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
