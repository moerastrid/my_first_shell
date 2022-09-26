/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   prompt.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: ageels <ageels@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/26 18:05:32 by ageels        #+#    #+#                 */
/*   Updated: 2022/09/26 21:56:06 by ageels        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	put_lst(t_token *temp)
{
	while (temp != NULL)
	{
		rl_replace_line(temp->data, 0);
		rl_on_new_line();
		rl_redisplay();
		temp = temp->next;
	}
}

int	prompt(void)
{
	t_token	*temp;
	char		*line;

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
		temp = tokenize(line);
		put_lst(temp);
	}
	free (line);
	rl_clear_history();
	return (0);
}
