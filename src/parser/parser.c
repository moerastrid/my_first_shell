/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: ageels <ageels@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/21 20:21:56 by ageels        #+#    #+#                 */
/*   Updated: 2022/10/24 16:56:08 by ageels        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static int	parse_words(t_cmd *cmd, t_token **tokens)
{
	int	type;

	while (1)
	{
		if ((*tokens) == NULL)
			return (0);
		type = (*tokens)->type;
		if (type & (WORD + QUOT + DQUOT + DOLL + DOLLQ))
		{
			add_arg(cmd, (*tokens)->data);
			return (0);
		}
		else if (type & WSPACE)
			*tokens = (*tokens)->next;
		else
			return (0);
	}
	return (0);
}

static int	parse_token(t_cmd *cmd, t_token **token)
{
	int	type;

	type = (*token)->type;
	if (type & (GREAT + LESS + GREATGREAT))
		return (parse_redirect(cmd, token));
	if (type & LESSLESS)
		return (parse_heredoc(cmd, token));
	if (type & (WORD + QUOT + DQUOT + DOLL + DOLLQ))
		return (parse_words(cmd, token));
	if (type == PIPE)
		return (cmd_add_pipe(cmd));
	return (0);
}

int	parse(t_cmd *cmd)
{
	t_token		*token;
	int			space_flag;
	int			ret;
	t_simple	*tail;

	substitute(*cmd, cmd->envc);
	cmd->paths = getpaths(cmd->envc);
	cmd->simples = new_simple(0, NULL);
	token = cmd->tokens;
	space_flag = 0;
	while (token != NULL)
	{
		ret = parse_token(cmd, &token);
		if (ret != 0)
			return (ret);
		if (token == NULL)
			break ;
		token = token->next;
	}
	cmd->cmd_count = count_simples(cmd);
	tail = simple_tail(cmd->simples);
	cmd_simples_set_bin(cmd);
	if (tail->argv == NULL)
		return (-1);
	return (0);
}
