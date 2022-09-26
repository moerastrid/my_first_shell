/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   prompt.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: ageels <ageels@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/26 18:05:32 by ageels        #+#    #+#                 */
/*   Updated: 2022/09/26 18:27:26 by ageels        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	prompt(void)
{
	rl_bind_key('\t', rl_complete);
	char	*line;

	line = NULL;
	while (1)
	{
		if (line)
			free (line);
		line = readline(" my_first_shell > ");
		if (!line)
			return (1);
		add_history (line);
	}
	free (line);
	return (0);
}
