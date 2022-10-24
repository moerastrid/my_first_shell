/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   heredoc.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: ageels <ageels@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/20 15:02:40 by ageels        #+#    #+#                 */
/*   Updated: 2022/10/24 19:51:53 by ageels        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "heredoc.h"
#include "../setup_reset/setup.h"

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

static int	token_check(t_cmd *cmd, t_token *lessless, t_token **token)
{
	if (!(*token))
	{
		printf("%s\n", "minishell : unexptected token newline");
		g_errno = 258;
		return (1);
	}
	if ((*token)->type & (WORD + QUOT + DQUOT + DOLL + DOLLQ))
		docadd_back(&cmd->doc, docnew(*token, lessless));
	else
	{
		printf("%s - %u\n", "minishell : unexptected token ", (*token)->type);
		g_errno = 258;
		return (1);
	}
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
			if (token_check(cmd, lessless, &token) == 1)
				return (1);
			token = lessless;
		}
		token = token->next;
	}
	if (cmd->doc != NULL)
		*retstr = heredoc_loop(cmd->doc, cmd);
	catch_signals();
	return (0);
}
