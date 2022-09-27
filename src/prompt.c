/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   prompt.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: ageels <ageels@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/26 18:05:32 by ageels        #+#    #+#                 */
/*   Updated: 2022/09/27 17:56:22 by ageels        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	prompt(void)
{
	t_token	*tok;
	char	*line;

	line = NULL;
	if (line)
		free (line);
	line = readline("my_first_shell > ");
	if (!line)
		return (1);
	if (line && *line)
	{
		add_history(line);
		tok = tokenize(line);
		while (tok != NULL)
		{
			printf("%d:[%s]\n", tok->type, tok->data);
			tok = tok->next;
		}
		ft_putstr_fd("\nhello \n", 1);
		rl_on_new_line();
		tok = NULL;
	}
	free (line);
	return (0);
}
