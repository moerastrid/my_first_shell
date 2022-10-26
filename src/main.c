/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: ageels <ageels@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/21 22:34:30 by ageels        #+#    #+#                 */
/*   Updated: 2022/10/26 19:22:54 by ageels        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	minishell(t_cmd *cmd, char **input, char **line)
{
	char	*retstr;

	retstr = NULL;
	if (*input == NULL)
		*line = prompt(cmd);
	else
		*line = *input;
	if (!ft_strlen(*line) || tokenize(cmd, *line) == -1 \
	|| !cmd->tokens || heredoc(cmd, &retstr))
		return (1);
	if (retstr != NULL)
	{
		reset(cmd, *line);
		*input = retstr;
		return (2);
	}
	g_errno = parse(cmd);
	if (g_errno == 0)
		g_errno = execute(cmd);
	return (1);
}

int	main(int argc, char **argv, char **envp)
{
	t_cmd	cmd;
	char	*input;
	char	*line;
	int		to_exit;
	int		res;

	input = NULL;
	line = NULL;
	to_exit = check_c_mode(argc, argv, &input);
	res = setup(&cmd, envp);
	if (res != 0)
		return (res);
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
	clear_cmd(&cmd);
	return (g_errno);
}

//ls | cat >out.txt <in.txt >>out2.txt | echo -e -r -m $SHLVL=a/b
