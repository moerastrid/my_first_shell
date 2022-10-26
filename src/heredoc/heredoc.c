/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   heredoc.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: ageels <ageels@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/20 15:02:40 by ageels        #+#    #+#                 */
/*   Updated: 2022/10/26 19:21:32 by ageels        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "heredoc.h"

static char	*heredoc_loop(t_doc *hd, t_cmd *cmd)
{
	char	*line;

	heredoc_signals();
	while (hd)
	{
		ft_putstr_fd(" >", STDERR_FILENO);
		line = readline(" ");
		if (g_errno == 1)
			return (line);
		if (!line || ft_strncmp(line, hd->eof, ft_strlen(hd->eof) + 1) == 0)
		{
			close(hd->fd);
			hd = hd->next;
		}
		else
		{
			if (hd->type == WORD)
				line = substitute_line(line, cmd->envc);
			write(hd->fd, line, ft_strlen(line));
			write(hd->fd, "\n", ft_strlen("\n"));
		}
		free(line);
	}
	return (NULL);
}

static int	token_check(t_cmd *cmd, t_token *lessless, t_token *token)
{
	if (!token)
		return (1);
	if (token->type & (WORD + QUOT + DQUOT + DOLL + DOLLQ))
		docadd_back(&cmd->doc, docnew(token, lessless));
	else
		return (1);
	return (0);
}

int	heredoc(t_cmd *cmd, char **retstr)
{
	t_token	*token;
	t_token	*lessless;

	cmd->doc = NULL;
	token = cmd->tokens;
	while (token)
	{
		if (token->type == LESSLESS)
		{
			lessless = token;
			token = token->next;
			while (token && token->type == WSPACE)
				token = token->next;
			if (token_check(cmd, lessless, token) == 1)
				return (0);
			token = lessless;
		}
		token = token->next;
	}
	if (cmd->doc != NULL)
		*retstr = heredoc_loop(cmd->doc, cmd);
	catch_signals();
	return (0);
}
