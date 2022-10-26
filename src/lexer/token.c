/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   token.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: ageels <ageels@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/14 14:29:43 by ageels        #+#    #+#                 */
/*   Updated: 2022/10/26 18:48:10 by ageels        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"

void	token_add_back(t_token **root, t_token *new)
{
	t_token	*node;

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

static void	merge_token_with_next(t_token *token)
{
	t_token	*temp;
	char	*new_data;

	if (token->next == NULL)
		return ;
	new_data = ft_strjoin(token->data, token->next->data);
	free(token->data);
	token->data = new_data;
	temp = token->next;
	token->next = token->next->next;
	free_token(temp);
}

void	merge_words(t_token *token)
{
	int		type;
	t_token	*next_token;
	int		next_type;

	while (token != NULL)
	{
		type = token->type;
		if (type & (WSPACE + PIPE + GREAT + GREATGREAT + LESS + LESSLESS))
		{
			token = token->next;
			continue ;
		}
		next_token = token->next;
		if (next_token == NULL)
			return ;
		next_type = next_token->type;
		if (next_type & (WORD + DOLL + QUOT + DQUOT + DOLLQ))
			merge_token_with_next(token);
		else
			token = token->next;
	}
}

void	remove_token_from_list(t_token **root, t_token *to_remove)
{
	t_token	*iter;

	if (!root || !*root || !to_remove)
		return ;
	if (*root == to_remove)
	{
		*root = to_remove->next;
		to_remove->next = NULL;
		free_token(to_remove);
		return ;
	}
	iter = *root;
	while (iter != NULL && iter->next != to_remove && iter != to_remove)
		iter = iter->next;
	if (iter == NULL)
		return ;
	iter->next = iter->next->next;
	to_remove->next = NULL;
	free_token(to_remove);
}
