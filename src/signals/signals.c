/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   signals.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: ageels <ageels@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/30 16:29:17 by ageels        #+#    #+#                 */
/*   Updated: 2022/10/03 18:11:42 by ageels        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "signal.h"

void	handle_sigint(int sig)
{
	int		i;
	pid_t	*temp;

	i = 0;
	temp = g_children;
	ft_putstr_fd("\n", STDERR_FILENO);
	rl_on_new_line();
	ft_putstr_fd("here\n", 2);
	while (&temp[i] != NULL)
	{
		kill (temp[i], SIGKILL);
		i++;
	}
}

void	handle_sigquit(int sig)
{
	return ;
}

void	catch_signals(void)
{
	struct sigaction	sa;

	sa.sa_handler = &handle_sigint;
	sa.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sa, NULL);
	//signal(SIGINT, &handle_sigint);
	signal(SIGQUIT, SIG_IGN);
}
