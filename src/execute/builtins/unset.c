/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ageels <ageels@student.codam.nl>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 14:02:35 by ageels            #+#    #+#             */
/*   Updated: 2022/10/14 18:35:21 by tnuyten          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execute.h"

int	bi_unset(t_simple simple, t_cmd *cmd)
{
	(void)simple;
	(void)cmd;
	ft_putstr_fd("unset is executed\n", 1);
	return (0);
}
