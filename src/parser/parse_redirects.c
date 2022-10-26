/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_redirects.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: ageels <ageels@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/21 22:29:17 by ageels        #+#    #+#                 */
/*   Updated: 2022/10/26 14:59:14 by ageels        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "../../minishell.h"

static void	simple_add(int type, t_simple *simple, char *data)
{
	if (type == GREAT || type == GREATGREAT)
	{
		simple_add_outfile(simple, data, type == GREATGREAT);
		return ;
	}
	simple_add_infile(simple, data, type == LESSLESS);
}

static void	ft_print_err(t_token *token)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd("syntax error near unexpected token `", STDERR_FILENO);
	if (token->type == LESS || token->type == LESSLESS)
		ft_putstr_fd("<", STDERR_FILENO);
	if (token->type == GREAT || token->type == GREATGREAT)
		ft_putstr_fd(">", STDERR_FILENO);
	if (token->type == PIPE)
		ft_putstr_fd("|", STDERR_FILENO);
	ft_putstr_fd("'\n", STDERR_FILENO);
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
			return (1);
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
	ft_print_err(*tokens);
	return (2);
}

int	parse_heredoc(t_cmd *cmd, t_token **token)
{
	simple_add_infile(simple_tail(cmd->simples), (*token)->data, 1);
	*token = (*token)->next;
	while (*token && (*token)->type == WSPACE)
		*token = (*token)->next;
	return (0);
}
