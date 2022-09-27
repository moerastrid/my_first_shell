/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   prompt.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: ageels <ageels@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/26 18:05:32 by ageels        #+#    #+#                 */
/*   Updated: 2022/09/27 21:10:33 by ageels        ########   odam.nl         */
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
