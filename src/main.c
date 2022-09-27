/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: ageels <ageels@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/26 16:54:53 by ageels        #+#    #+#                 */
/*   Updated: 2022/09/27 22:24:00 by ageels        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	main(int argc, char **argv, char **envp)
{
	char	*line;
	t_cmd	cmds;

	line = NULL;
	while (1)
	{
		line = prompt();
		if (!line)
			return (1);
		if (*line)
		{
			printf("\nRETURN VALUES:\nPARSE:\t\t%d\n", parse(line, &cmds, envp));
			printf("EXECUTE:\t%d\n", execute(cmds));
		}
		free(line);
		line = NULL;
	}
	rl_clear_history();
	return (0);
}
