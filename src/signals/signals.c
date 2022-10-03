/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   signals.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: ageels <ageels@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/30 16:29:17 by ageels        #+#    #+#                 */
/*   Updated: 2022/10/03 21:49:38 by ageels        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "signal.h"

void	handle_sigint(int sig)
{
	ft_putstr_fd("\n", STDERR_FILENO);
	rl_on_new_line();
	rl_redisplay();
	//while (temp != NULL)
	//{
	//	kill (temp->id, SIGKILL);
	//	temp = temp->next;
	//}

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
