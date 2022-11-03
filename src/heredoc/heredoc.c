/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   heredoc.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: ageels <ageels@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/20 15:02:40 by ageels        #+#    #+#                 */
/*   Updated: 2022/11/03 15:53:49 by ageels        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "heredoc.h"

static void	heredoc_loop(t_doc *hd, t_cmd *cmd)
{
	char	*indoc;

	default_signals();
	while (hd)
	{
		ft_putstr_fd(" >", STDERR_FILENO);
		indoc = readline(" ");
		if (!indoc || ft_strncmp(indoc, hd->eof, ft_strlen(hd->eof) + 1) == 0)
		{
			close(hd->fd);
			hd = hd->next;
		}
		else
		{
			if (hd->type == WORD)
				indoc = substitute_line(indoc, cmd->envc);
			ft_putstr_fd(indoc, hd->fd);
			ft_putstr_fd("\n", hd->fd);
		}
		free(indoc);
	}
	exit(0);
}

static int	heredoc_process(t_doc *hd, t_cmd *cmd)
{
	pid_t	heredoc_id;

	heredoc_id = fork();
	if (heredoc_id == -1)
		return (-1);
	else if (heredoc_id == 0)
	{
		heredoc_loop(hd, cmd);
	}
	ignore_signals();
	return (signal_catcher(heredoc_id));
}

static int	doc_add(t_cmd *cmd, t_token *lessless, t_token *token)
{
	if (!token)
		return (1);
	if (token->type & (WORD + QUOT + DQUOT + DOLL + DOLLQ))
		docadd_back(&cmd->doc, docnew(token, lessless));
	else
		return (1);
	return (0);
}

int	heredoc(t_cmd *cmd)
{
	t_token	*token;
	t_token	*lessless;

	token = cmd->tokens;
	while (token)
	{
		if (token->type == LESSLESS)
		{
			lessless = token;
			token = token->next;
			while (token && token->type == WSPACE)
				token = token->next;
			if (doc_add(cmd, lessless, token) == 1)
				return (0);
			token = lessless;
		}
		token = token->next;
	}
	if (cmd->doc != NULL)
	{
		cmd->err = heredoc_process(cmd->doc, cmd);
		return (cmd->err);
	}
	return (0);
}
