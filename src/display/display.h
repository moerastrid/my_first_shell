/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   display.h                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: ageels <ageels@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/30 16:27:35 by ageels        #+#    #+#                 */
/*   Updated: 2022/10/10 16:13:53 by ageels        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNAL_H
# define SIGNAL_H

# include "../../minishell.h"
# include <termios.h>

# define PROMPT " (⁠╯⁠°⁠□⁠°⁠）⁠╯⁠︵⁠ ⁠┻⁠━⁠┻ "

void	handle_sigint(int sig);
void	setup_termios(void);

#endif