/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   touch_children.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: ageels <ageels@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/14 14:24:45 by ageels        #+#    #+#                 */
/*   Updated: 2022/10/31 22:08:12 by ageels        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

t_children	*new_child(pid_t id)
{
	t_children	*new;

	new = ft_calloc(1, sizeof(t_children));
	if (new == NULL)
		return (NULL);
	new->id = id;
	new->next = NULL;
	return (new);
}

void	child_add_back(t_children **root, t_children *new)
{
	t_children *temp;

	temp = *root;
	if (root == NULL)
		return ;
	if (*root == NULL)
	{
		*root = new;
		return ;
	}
	while (temp->next != NULL)
		temp = temp->next;
	temp->next = new;
}
