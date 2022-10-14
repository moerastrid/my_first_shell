/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   errors.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: ageels <ageels@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/12 22:16:11 by ageels        #+#    #+#                 */
/*   Updated: 2022/10/14 12:58:58 by ageels        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "display.h"

void	catch_errno(int err)
{
	if (g_errno != 0)
		dprintf(STDERR_FILENO, "OH NOOOO ~ error! %d\n", g_errno);
	if (g_errno == 130)
		ft_putstr_fd("^C\n", STDERR_FILENO);
	if (g_errno == 131)
		ft_putstr_fd("^\\Quit:3\n", STDERR_FILENO);
}
