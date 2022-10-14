/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   setup.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: ageels <ageels@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/10 15:59:54 by ageels        #+#    #+#                 */
/*   Updated: 2022/10/14 16:56:52 by ageels        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	setup_termios(void)
{
	struct termios	my_term;

	if (tcgetattr(0, &my_term) == -1)
		g_errno = errno;
	my_term.c_lflag &= ~ECHOCTL;
	if (tcsetattr(0, 0, &my_term) == -1)
		g_errno = errno;
}

static char	**copy_env(char **og)
{
	char	**copy;
	int		i;

	copy = NULL;
	i = 0;
	while (og[i] != NULL)
	{
		i++;
	}
	copy = ft_calloc(i + 1, sizeof(char *));
	if (copy == NULL)
		return (NULL);
	i = 0;
	while (og[i] != NULL)
	{
		copy[i] = ft_strdup(og[i]);
		i++;
	}
	return (copy);
}

int	setup(t_cmd *cmd, char **envp, int argc)
{
	if (argc != 1)
	{
		ft_putstr_fd("Minishell doesn't want an argument, please try again\n", \
		STDERR_FILENO);
		return (-1);
	}
	g_errno = 0;
	setup_termios();
	if (g_errno != 0)
		return (-1);
	catch_signals();
	cmd->cmd_count = 0;
	cmd->simples = NULL;
	cmd->outfiles = NULL;
	cmd->infiles = NULL;
	cmd->delimiters = NULL;
	cmd->envc = copy_env(envp);
	if (!cmd->envc)
		return (-1);
	return (0);
}
