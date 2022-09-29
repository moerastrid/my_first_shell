/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   prompt.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: ageels <ageels@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/27 22:19:13 by ageels        #+#    #+#                 */
/*   Updated: 2022/09/29 23:03:26 by ageels        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*prompt(void)
{
	char	*line;

	line = readline(" > ");
	if (!line)
		return (NULL);
	if (*line)
		add_history(line);
	return (line);
}
