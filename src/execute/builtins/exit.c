/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exit.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: ageels <ageels@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/12 14:12:13 by ageels        #+#    #+#                 */
/*   Updated: 2022/10/21 23:40:53 by ageels        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../execute.h"

void	bi_exit(t_cmd *cmd)
{
	int ret;

	ret = 0;
	if (cmd->cmd_count == 1)
		ft_putstr_fd("exit\n", STDERR_FILENO);
	if (cmd->simples->argv[1])
		ret = ft_atoi(cmd->simples->argv[1]);
	clear_cmd(cmd);
	exit (ret);
}
