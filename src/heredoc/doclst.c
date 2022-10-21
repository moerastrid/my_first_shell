/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   doclst.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: ageels <ageels@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/21 22:02:27 by ageels        #+#    #+#                 */
/*   Updated: 2022/10/21 22:04:00 by ageels        ########   odam.nl         */
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
	{
		g_errno = 12;
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

t_doc	*docnew(char *eof, t_token *lessless)
{
	t_doc	*new;

	new = malloc(sizeof(t_doc));
	if (!new)
	{
		g_errno = 12;
		return (NULL);
	}
	new->name = nextfilename(ft_strdup("heredob"));
	lessless->data = new->name;
	new->fd = open(new->name, O_CREAT | O_RDWR, 0664);
	new->eof = ft_strdup(eof);
	new->next = NULL;
	return (new);
}