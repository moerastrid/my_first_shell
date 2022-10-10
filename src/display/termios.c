/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   termios.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: ageels <ageels@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/10 15:59:54 by ageels        #+#    #+#                 */
/*   Updated: 2022/10/10 16:17:45 by ageels        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "display.h"

void	setup_termios(void)
{
	struct termios	my_term;

	tcgetattr(0, &my_term);
	my_term.c_lflag &= ~ECHOCTL;
	tcsetattr(0, 0, &my_term);
}
