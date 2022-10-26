/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_redirects.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: ageels <ageels@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/21 22:29:17 by ageels        #+#    #+#                 */
/*   Updated: 2022/10/26 19:22:16 by ageels        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static void	simple_add(int type, t_simple *simple, char *data)
{
	if (type == GREAT || type == GREATGREAT)
	{
		simple_add_outfile(simple, data, type == GREATGREAT);
		return ;
	}
	simple_add_infile(simple, data, type == LESSLESS);
}

static int	ft_print_err(t_token *token, int err)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd("syntax error near unexpected token `", STDERR_FILENO);
	if (token == NULL)
		ft_putstr_fd("newline", STDERR_FILENO);
	else if (token->type == LESS || token->type == LESSLESS)
		ft_putstr_fd("<", STDERR_FILENO);
	else if (token->type == GREAT || token->type == GREATGREAT)
		ft_putstr_fd(">", STDERR_FILENO);
	else if (token->type == PIPE)
		ft_putstr_fd("|", STDERR_FILENO);
	ft_putstr_fd("'\n", STDERR_FILENO);
	return (err);
}

int	parse_redirect(t_cmd *cmd, t_token **tokens)
{
	int		type;
	int		start_type;

	start_type = (*tokens)->type;
	*tokens = (*tokens)->next;
	while (1)
	{
		if ((*tokens) == NULL)
			return (ft_print_err(*tokens, 2));
		type = (*tokens)->type;
		if (type == WSPACE)
			*tokens = (*tokens)->next;
		else if (type & (QUOT + DQUOT + WORD + DOLL + DOLLQ))
		{
			simple_add(start_type, simple_tail(cmd->simples), (*tokens)->data);
			return (0);
		}
		else
			break ;
		continue ;
	}
	return (ft_print_err(*tokens, 2));
}

int	parse_heredoc(t_cmd *cmd, t_token **token)
{
	if ((*token)->data)
	{
		simple_add_infile(simple_tail(cmd->simples), (*token)->data, 1);
		*token = (*token)->next;
		while (*token && (*token)->type == WSPACE)
		*token = (*token)->next;
	}
	else
		return (ft_print_err(NULL, 2));
	return (0);
}
