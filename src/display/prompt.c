/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   prompt.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: ageels <ageels@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/10 15:09:05 by ageels        #+#    #+#                 */
/*   Updated: 2022/10/10 16:14:03 by ageels        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "display.h"

char	*prompt(void)
{
	char	*line;

	line = readline(PROMPT);
	if (line == NULL)
	{
		ft_putstr_fd("exit on line = NULL\n", STDERR_FILENO);
		exit(0);
	}
	if (*line)
		add_history(line);
	return (line);
}
