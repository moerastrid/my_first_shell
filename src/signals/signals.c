/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   signals.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: ageels <ageels@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/30 16:29:17 by ageels        #+#    #+#                 */
/*   Updated: 2022/10/04 16:46:17 by ageels        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "signal.h"

void	handle_sigint(int sig)
{
	t_children *temp;

	*temp = g_children;
	ft_putstr_fd("\n", STDERR_FILENO);
	rl_on_new_line();
	rl_redisplay();
	while (temp != NULL)
	{
		temp->id = -1;
		temp = temp->next;
	}
}

void	handle_sigquit(int sig)
{
	return ;
}

void	catch_signals(void)
{
	signal(SIGINT, &handle_sigint);
	signal(SIGQUIT, SIG_IGN);
}
