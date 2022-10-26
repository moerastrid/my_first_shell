/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   str_list.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: ageels <ageels@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/14 15:43:27 by ageels        #+#    #+#                 */
/*   Updated: 2022/10/26 19:22:33 by ageels        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_str_list	*str_list_new(char *str, int append_mode)
{
	t_str_list	*new;

	new = ft_calloc(1, sizeof(t_str_list));
	if (new == NULL)
		return (NULL);
	new->str = NULL;
	if (str)
		new->str = ft_strdup(str);
	new->append_mode = append_mode;
	new->next = NULL;
	return (new);
}

void	str_list_add_back(t_str_list *root, t_str_list *new)
{
	if (root == NULL)
		return ;
	while (root->next != NULL)
		root = root->next;
	root->next = new;
}

void	free_str_list(t_str_list *root)
{
	t_str_list	*temp;

	while (root != NULL)
	{
		free(root->str);
		temp = root->next;
		free(root);
		root = temp;
	}
	root = NULL;
}
