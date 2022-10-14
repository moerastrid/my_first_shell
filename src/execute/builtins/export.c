/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ageels <ageels@student.codam.nl>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 14:12:13 by ageels            #+#    #+#             */
/*   Updated: 2022/10/14 18:29:29 by tnuyten          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execute.h"

//cmd pointer needs to be passed by reference back to main and envp not freed at reset.
int	bi_export(t_simple simple, t_cmd *cmd)
{
	cmd->envc = env_add(simple.argv[0], cmd->envc);

	return (0);
}
