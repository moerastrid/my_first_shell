/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ageels <ageels@student.codam.nl>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 22:19:53 by ageels            #+#    #+#             */
/*   Updated: 2022/09/26 13:48:03 by tnuyten          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <stdio.h>

/// @brief	here we execute one command
/// @param	cmds the list with all commands
/// @param	cmd_no	the command we want to execute
void	exec_cmd(t_list *cmds, int cmd_no)
{
	static int	i = 0;

	i++;
	printf("cmd %d is executed\n", i);
	exit(0);
}
