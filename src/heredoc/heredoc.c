/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   heredoc.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: ageels <ageels@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/20 15:02:40 by ageels        #+#    #+#                 */
/*   Updated: 2022/10/21 17:05:50 by ageels        ########   odam.nl         */
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

static void	heredoc_loop(t_doc *heredoc)
{
	char	*line;
	t_doc	*temp;

	while (heredoc)
	{
		line = readline(" > ");
		if (!line)
		{
			temp = heredoc;
			heredoc = heredoc->next;
			close(temp->fd);
			free (temp);
		}
		else if (ft_strncmp(line, heredoc->eof, ft_strlen(heredoc->eof) + 1) == 0)
		{
			temp = heredoc;
			heredoc = heredoc->next;
			close(temp->fd);
			free (temp);
		}
		else
		{
			write(heredoc->fd, line, ft_strlen(line));
			write(heredoc->fd, "\n", ft_strlen("\n"));
		}
		free(line);
	}
	return ;
}

void	heredoc(t_cmd *cmd)
{
	t_doc	*doc;
	t_token	*tokens;
	t_token	*lessless;

	doc = NULL;
	tokens = cmd->tokens;
	while (tokens)
	{
		if (tokens->type == LESSLESS)
		{
			lessless = tokens;
			tokens = tokens->next;
			while (tokens && tokens->type == WSPACE)
				tokens = tokens->next;
			if (!tokens)
				return ;
			if (tokens->type & (WORD + QUOT + DQUOT + DOLL + DOLLQ))
			{
				docadd_back(&doc, docnew(tokens->data, lessless));
				remove_token_from_list(&cmd->tokens, tokens);
				tokens = lessless;
			}
		}
		tokens = tokens->next;
	}
	if (doc != NULL)
		heredoc_loop(doc);
}
