/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cd.c                                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: ageels <ageels@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/12 14:12:13 by ageels        #+#    #+#                 */
/*   Updated: 2022/10/17 16:16:38 by ageels        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../execute.h"

int	bi_cd(t_simple *simple, t_cmd *cmd)
{
	if (simple->argc == 1)
		chdir(find_str("HOME", cmd->envc) + 5);
		// go to home dir function
	else
		chdir(simple->argv[1]);
	// update pwd in envc
	return (0);
}
