/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: ageels <ageels@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/26 16:54:53 by ageels        #+#    #+#                 */
/*   Updated: 2022/09/26 17:00:16 by ageels        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	main(int argc, char **argv, char **envp)
{
	char *line = readline("Enter a line: ");
	//execute();
	//free_structs();
	t_cmd	cmds;
	cmds.amount_cmd = 4;
	//family_life(cmds);
}
