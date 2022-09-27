/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   prompt.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: ageels <ageels@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/26 18:05:32 by ageels        #+#    #+#                 */
/*   Updated: 2022/09/27 18:22:59 by ageels        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char*	prompt(void)
{
	t_token	*tok;
	char	*line;
	char	*return_string;

	return_string = NULL;
	line = readline("my_first_shell > ");
	if (!line)
		return (NULL);
	if (*line)
	{
		add_history(line);
		return_string = ft_strjoin(line, return_string);
		ft_putstr_fd("\nhello \n", 1);
		rl_on_new_line();
		tok = NULL;
	}
	free (line);
	return (return_string);
}
