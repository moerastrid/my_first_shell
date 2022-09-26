/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   prompt.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: ageels <ageels@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/26 18:05:32 by ageels        #+#    #+#                 */
/*   Updated: 2022/09/26 22:06:47 by ageels        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"



int	prompt(void)
{
	t_token	*temp;
	char		*line;

	line = NULL;
	while (1)
	{
		if (line)
			free (line);
		line = readline("my_first_shell > ");
		if (!line)
			return (1);
		if (line && *line)
			add_history (line);
		ft_putstr_fd("my_first_shell: ", 1);
		ft_putstr_fd(line, 1);
		ft_putstr_fd(": command not found\n", 1);
		rl_on_new_line();
	}
	free (line);
	rl_clear_history();
	return (0);
}
