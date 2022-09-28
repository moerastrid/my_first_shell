/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnuyten <tnuyten@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 19:29:49 by tnuyten           #+#    #+#             */
/*   Updated: 2021/10/26 23:24:40 by tnuyten          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*ref;
	t_list	*cur;

	if (!lst)
		return ;
	ref = lst[0];
	while (ref->next)
	{
		cur = ref;
		ref = ref->next;
		ft_lstdelone(cur, del);
	}
	ft_lstdelone(ref, del);
	*lst = NULL;
}
