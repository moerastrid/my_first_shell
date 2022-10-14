/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exit.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: ageels <ageels@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/12 14:12:13 by ageels        #+#    #+#                 */
/*   Updated: 2022/10/14 14:02:05 by ageels        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../execute.h"

void	bi_exit(t_cmd cmd)
{
	clear_cmd(&cmd); //What's the point in taking the reference here?
	if (cmd.cmd_count == 1)
		ft_putstr_fd("exit\n", STDERR_FILENO);
	exit (0);
}
