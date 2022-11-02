/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: ageels <ageels@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/14 14:29:48 by ageels        #+#    #+#                 */
/*   Updated: 2022/10/26 18:45:09 by ageels        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"

int	is_token_char(char *str)
{
	if (ft_strncmp(str, "$", 1) == 0)
		return (1);
	if (ft_strncmp(str, "|", 1) == 0)
		return (1);
	if (ft_strncmp(str, ">", 1) == 0)
		return (1);
	if (ft_strncmp(str, "<", 1) == 0)
		return (1);
	if (ft_strncmp(str, "\"", 1) == 0)
		return (1);
	if (ft_strncmp(str, "'", 1) == 0)
		return (1);
	return (0);
}

int	token_type(char *str)
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
	if (ft_strncmp(str, " ", 1) == 0)
		return (WSPACE);
	if (ft_strncmp(str, "\t", 1) == 0)
		return (WSPACE);
	if (ft_strncmp(str, "\n", 1) == 0)
		return (WSPACE);
	return (WORD);
}

void	token_delete_empty_subs(t_cmd *cmd)
{
	t_token	*token;
	t_token	*next;

	token = cmd->tokens;
	while (token)
	{
		next = token->next;
		if (token->type & (WORD + DOLL))
		{
			if (token->data == NULL || ft_strlen(token->data) == 0)
				remove_token_from_list(&(cmd->tokens), token);
		}
		token = next;
	}
}
