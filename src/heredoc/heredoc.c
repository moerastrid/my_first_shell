/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   heredoc.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: ageels <ageels@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/20 15:02:40 by ageels        #+#    #+#                 */
/*   Updated: 2022/10/21 19:00:48 by ageels        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "heredoc.h"

static char	*nextfilename(char *s)
{
	char	*ret;
	int		i;

	i = 0;
	ret = NULL;
	ret = ft_calloc(ft_strlen(s) + 1, sizeof(char));
	if (!ret)
		return (NULL);
	while (s[i])
	{
		ret[i] = s[i];
		i++;
	}
	ret[i - 1] = s[i - 1] + 1;
	free(s);
	if (access(ret, F_OK) == 0)
		ret = nextfilename(ret);
	return (ret);
}

static void	docadd_back(t_doc **doc, t_doc *new_doc)
{
	t_doc	*temp;

	if (!doc)
		return ;
	temp = doc[0];
	if (temp == NULL)
	{
		doc[0] = new_doc;
		return ;
	}
	while (temp->next != NULL)
		temp = temp->next;
	temp->next = new_doc;
}

static t_doc	*docnew(char *eof, t_token *lessless)
{
	t_doc	*new;

	new = malloc(sizeof(t_doc));
	if (!new)
		return (NULL);
	new->name = nextfilename(ft_strdup("heredob"));
	lessless->data = new->name;
	new->fd = open(new->name, O_CREAT | O_RDWR, 0664);
	new->eof = ft_strdup(eof);
	new->next = NULL;
	return (new);
}

char	*heredoc_loop(t_doc *heredoc)
{
	char	*line;

	while (heredoc)
	{
		ft_putstr_fd(" >", STDERR_FILENO);
		line = readline(" ");
		if (g_errno == 1)
			return (line);
		if (!line || ft_strncmp(line, heredoc->eof, ft_strlen(heredoc->eof) + 1) == 0)
		{
			close(heredoc->fd);
			heredoc = heredoc->next;
		}
		else
		{
			write(heredoc->fd, line, ft_strlen(line));
			write(heredoc->fd, "\n", ft_strlen("\n"));
		}
		free(line);
	}
	return (NULL);
}

int	heredoc(t_cmd *cmd, char **retstr)
{
	t_token	*token;
	t_token	*lessless;

	heredoc_signals();
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
			if (!token)
			{
				printf("%s\n", "unexptected token newline");
				return (1);
			}
			if (token->type & (WORD + QUOT + DQUOT + DOLL + DOLLQ))
			{
				docadd_back(&cmd->doc, docnew(token->data, lessless));
				remove_token_from_list(&cmd->tokens, token);
				token = lessless;
			}
			else
			{
				printf("%s - %u\n", "unexptected token ", token->type);
				return (1);
			}
		}
		token = token->next;
	}
	if (cmd->doc != NULL)
		*retstr = heredoc_loop(cmd->doc);
	catch_signals();
	return (0);
}
