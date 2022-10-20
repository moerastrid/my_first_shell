/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exit.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: ageels <ageels@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/12 14:12:13 by ageels        #+#    #+#                 */
/*   Updated: 2022/10/20 20:55:39 by ageels        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../execute.h"

void	bi_exit(t_cmd *cmd)
{
	if (cmd->cmd_count == 1)
		ft_putstr_fd("exit\n", STDERR_FILENO);
	clear_cmd(cmd);
	exit (0);
}
