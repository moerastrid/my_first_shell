/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   setup.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: ageels <ageels@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/10 15:59:54 by ageels        #+#    #+#                 */
/*   Updated: 2022/10/20 21:22:24 by ageels        ########   odam.nl         */
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

static int	setup_cmd(t_cmd *cmd, char **envp)
{
	char	*str;
	int		lvl;

	cmd->cmd_count = 0;
	cmd->simples = NULL;
	cmd->tokens = NULL;
	cmd->paths = NULL;
	cmd->envc = copy_env(envp);
	if (!cmd->envc)
		return (-1);
	str = find_str("SHLVL", cmd->envc) + 6;
	if (str == NULL)
		return (0);
	lvl = ft_atoi(str) + 1;
	str = NULL;
	str = ft_strjoin("SHLVL=", ft_itoa(lvl));
	if (env_replace("SHLVL", str, cmd->envc) == -1)
		free(str);
	return (0);
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
	return (setup_cmd(cmd, envp));
}
