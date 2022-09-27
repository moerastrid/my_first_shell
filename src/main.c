/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: ageels <ageels@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/26 16:54:53 by ageels        #+#    #+#                 */
/*   Updated: 2022/09/26 22:15:38 by ageels        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	main(int argc, char **argv, char **envp)
{
	while (1)
	{
	if (prompt() != 0)
		return (1);
	}
	rl_clear_history();
	return (0);
	//execute();
	//free_structs();

	// cmds.amount_cmd = 4;
	//family_life(cmds);
}
