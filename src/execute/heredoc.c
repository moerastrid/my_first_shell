/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   heredoc.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: ageels <ageels@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/20 15:02:40 by ageels        #+#    #+#                 */
/*   Updated: 2022/10/20 20:19:13 by ageels        ########   odam.nl         */
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

t_doc	*docnew(char *eof, int no)
{
	t_doc	*new;

	new = malloc(sizeof(t_doc));
	if (!new)
		return (NULL);
	new->name = nextfilename(ft_strdup("heredob"));
	new->fd = open(new->name, O_CREAT | O_RDWR, 0664);
	new->no = no;
	new->eof = ft_strdup(eof);
	new->next = NULL;
	return (new);
}

static t_doc	*doc_delfirst(t_doc *heredoc)
{
	t_doc	*temp;
	t_doc	*retdoc;

	retdoc = heredoc->next;
	temp = heredoc;
	close(temp->fd);
	if (retdoc)
		unlink(temp->name);
	free(temp->name);
	free(temp);
	return (retdoc);
}

char	*heredoc_loop(t_doc *heredoc)
{
	char	*line;
	char	*retstr;

	while (heredoc)
	{
		retstr = ft_strdup(heredoc->name);
		line = readline(" > ");
		if (!line || !retstr)
			exit (-1);
		if (ft_strncmp(line, heredoc->eof, ft_strlen(heredoc->eof) + 1) == 0)
		{
			heredoc = doc_delfirst(heredoc);
			if (heredoc != NULL)
			{
				free (retstr);
				retstr = ft_strdup(heredoc->name);
			}
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
