/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ageels <ageels@student.codam.nl>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 18:05:32 by ageels            #+#    #+#             */
/*   Updated: 2022/09/27 17:14:11 by tnuyten          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"



char	**prompt(void)
{
	t_token	*temp;
	char	*line;
	t_cmd cmd;

	while (1)
	{
		line = readline("my_first_shell > ");
		if (!line)
			return (NULL);
		if (line && *line)
			add_history (line);
		// ft_putstr_fd("my_first_shell: ", 1);
		// ft_putstr_fd(line, 1);
		// ft_putstr_fd(": command not found\n", 1);
		parse(line, &cmd); //Temporary. ...?
		rl_on_new_line();
		free (line);
	}
	//rl_clear_history();
	return (0);
}
