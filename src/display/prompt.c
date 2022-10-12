/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   prompt.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: ageels <ageels@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/10 15:09:05 by ageels        #+#    #+#                 */
/*   Updated: 2022/10/12 15:37:09 by ageels        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "display.h"

char	*prompt(void)
{
	char	*line;

	line = readline(PROMPT);
	if (line == NULL)
	{
		rl_on_new_line();
		//ft_putendl_fd("", 1); //Lijkt nodig te zijn op linux?
		exit(0);
	}
	if (*line)
		add_history(line);
	return (line);
}
