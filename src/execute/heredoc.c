/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   heredoc.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: ageels <ageels@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/20 15:02:40 by ageels        #+#    #+#                 */
/*   Updated: 2022/10/21 16:06:35 by ageels        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

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

void	docadd_back(t_doc **doc, t_doc *new_doc)
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

t_doc	*docnew(char *eof, int no, t_token *lessless)
{
	t_doc	*new;

	new = malloc(sizeof(t_doc));
	if (!new)
		return (NULL);
	new->name = nextfilename(ft_strdup("heredob"));
	lessless->data = new->name;
	new->fd = open(new->name, O_CREAT | O_RDWR, 0664);
	new->no = no;
	new->eof = ft_strdup(eof);
	new->next = NULL;
	return (new);
}

char	*heredoc_loop(t_doc *heredoc)
{
	char	*line;
	t_doc	*temp;

	while (heredoc)
	{
		line = readline(" > ");
		if (!line)
			exit (-1);
		if (ft_strncmp(line, heredoc->eof, ft_strlen(heredoc->eof) + 1) == 0)
		{
			temp = heredoc;
			heredoc = heredoc->next;
			free (temp);
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

void	heredoc(t_cmd *cmd)
{
	t_doc	*doc;
	t_token	*tokens;
	int		heredoc_count;
	t_token *lessless;

	doc = NULL;
	heredoc_count = 0;
	tokens = cmd->tokens;
	while (tokens)
	{
		if(tokens->type == LESSLESS)
		{
			lessless = tokens;
			tokens = tokens->next;
			while(tokens && tokens->type == WSPACE)
				tokens = tokens->next;
			if (!tokens)
				return ;
			if(tokens->type & (WORD + QUOT + DQUOT + DOLL + DOLLQ))
			{
				docadd_back(&doc, docnew(tokens->data, heredoc_count++, lessless));
				//t_token *next_token = tokens->next; todo: remove word after LESSLESS.
				//lessless->next = lessless->next->next;
			}
			else
			{
				//parse error near ' ' 
				g_errno = -1;
			}
		}
		tokens = tokens->next;
	}
	if (heredoc_count != 0)
	{
		heredoc_loop(doc);
	}
	return ;
}
