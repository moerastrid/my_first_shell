/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   errors.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: ageels <ageels@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/12 22:16:11 by ageels        #+#    #+#                 */
/*   Updated: 2022/10/17 23:22:04 by ageels        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "display.h"

void	catch_errno(int err)
{
	(void)err;
	//if (g_errno != 0)
	//	dprintf(STDERR_FILENO, "OH NOOOO ~ error! %d\n", g_errno);
	if (g_errno == -1)
		ft_putstr_fd("minishell : syntax error near unexpected token '|'\n", STDERR_FILENO);
	else if (g_errno == 2)
		return ;
	else if (g_errno == 10 || g_errno == 11 || g_errno == 12 || g_errno == 13)
		ft_putstr_fd("minishell: syntax error near unexpected token: [??]\n", STDERR_FILENO);
	else if (g_errno == 130)
		ft_putstr_fd("^C\n", STDERR_FILENO);
	else if (g_errno == 131)
		ft_putstr_fd("^\\Quit: 3\n", STDERR_FILENO);
	else if (errno != 0 && errno != 2 && errno != 130 && errno != 131)
	{
		ft_putstr_fd(strerror(errno), STDERR_FILENO);
		ft_putstr_fd("\n", STDERR_FILENO);
	}
}
