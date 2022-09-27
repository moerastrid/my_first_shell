/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   prompt.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: ageels <ageels@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/27 22:19:13 by ageels        #+#    #+#                 */
/*   Updated: 2022/09/27 22:19:15 by ageels        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*prompt(void)
{
	char	*line;

	line = readline("my_first_shell > ");
	if (!line)
		return (NULL);
	if (*line)
		add_history(line);
	return (line);
}
