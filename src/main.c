/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: ageels <ageels@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/21 22:34:30 by ageels        #+#    #+#                 */
/*   Updated: 2022/10/24 19:38:58 by ageels        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "heredoc/heredoc.h"
#include "substitutor/substitutor.h"

int	minishell(t_cmd *cmd, char **input, char **line)
{
	char	*retstr;

	retstr = NULL;
	if (*input == NULL)
		*line = prompt(cmd);
	else
		*line = *input;
	if (ft_strlen(*line) == 0 || tokenize(cmd, *line) == -1 \
	|| cmd->tokens == NULL || heredoc(cmd, &retstr))
		return (1);
	if (retstr != NULL)
	{
		reset(cmd, *line);
		*input = retstr;
		return (2);
	}
	if (parse(cmd) != 0)
		return (1);
	g_errno = execute(cmd);
	return (1);
}

int	main(int argc, char **argv, char **envp)
{
	t_cmd	cmd;
	char	*input;
	char	*line;
	int		to_exit;

	input = NULL;
	to_exit = check_c_mode(argc, argv, &input);
	line = NULL;
	if (setup(&cmd, envp) == -1)
		return (-1);
	while (1)
	{
		if (minishell(&cmd, &input, &line) == 1)
		{
			input = NULL;
			reset(&cmd, line);
		}
		if (to_exit)
			break ;
	}
	return (g_errno);
}

//ls | cat >out.txt <in.txt >>out2.txt | echo -e -r -m $SHLVL=a/b
