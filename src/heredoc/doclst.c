/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   doclst.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: ageels <ageels@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/21 22:02:27 by ageels        #+#    #+#                 */
/*   Updated: 2022/10/31 22:15:54 by ageels        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "heredoc.h"

static char	*nextfilename(char *s)
{
	char	*ret;
	int		i;

	i = 0;
	ret = ft_calloc(ft_strlen(s) + 1, sizeof(char));
	if (!ret)
	{
		free (s);
		return (NULL);
	}
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

t_doc	*docnew(t_token *token, t_token *lessless)
{
	t_doc	*new;

	new = ft_calloc(1, sizeof(t_doc));
	if (!new)
		return (NULL);
	new->name = nextfilename(ft_strdup("heredob"));
	if (new->name == NULL)
		return (NULL);
	lessless->data = ft_strdup(new->name);
	if (lessless->data == NULL)
		return (NULL);
	new->fd = open(new->name, O_CREAT | O_RDWR, 0664);
	if (token->type == DOLL)
		new->eof = ft_strjoin("$", token->data);
	else
		new->eof = ft_strdup(token->data);
	new->type = token->type;
	new->next = NULL;
	return (new);
}

static void	doc_free(t_doc *doc)
{
	if (!doc)
		return ;
	if (doc->name)
		free(doc->name);
	close(doc->fd);
	if (doc->eof)
		free(doc->eof);
	free(doc);
}

void	docs_free(t_doc *doc)
{
	t_doc	*next;

	while (doc)
	{
		next = doc->next;
		doc_free(doc);
		doc = next;
	}
}
