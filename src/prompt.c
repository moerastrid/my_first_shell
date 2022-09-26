/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   prompt.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: ageels <ageels@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/26 18:05:32 by ageels        #+#    #+#                 */
/*   Updated: 2022/09/26 20:03:06 by ageels        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	prompt(void)
{
	char	*line;

	line = NULL;
	while (1)
	{
		if (line)
			free (line);
		line = readline(" my_first_shell > ");
		if (!line)
			return (1);
		if (line && *line)
			add_history (line);
	}
	free (line);
	rl_clear_history();
	return (0);
}
