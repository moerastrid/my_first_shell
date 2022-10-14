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

int	bi_export(t_simple simple, t_cmd *cmd)
{
	print_simples(cmd);

	cmd->envc = env_add(simple.argv[0], cmd->envc);

	char **envc_c = cmd->envc;

	while(*envc_c)
	{
		printf("%s\n", *envc_c++);
	}

	ft_putstr_fd("buildin is executed\n", 1);
	return (0);
}
