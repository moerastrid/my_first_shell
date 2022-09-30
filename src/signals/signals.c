/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   signals.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: ageels <ageels@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/30 16:29:17 by ageels        #+#    #+#                 */
/*   Updated: 2022/09/30 18:24:50 by ageels        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "signal.h"

void	handle_the_d(int sig)
{
	kill(0, SIGKILL);
}

void	handle_sigint(int sig)
{
	int		i;
	pid_t	*temp;

	i = 0;
	temp = g_children;
	ft_putstr_fd("\n", STDERR_FILENO);
	rl_on_new_line();
	rl_redisplay();
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
	signal(SIGINT, &handle_sigint);
	signal(SIGQUIT, NULL);
	//signal(D, &handle_the_d);
}
