/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   display.h                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: ageels <ageels@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/30 16:27:35 by ageels        #+#    #+#                 */
/*   Updated: 2022/10/21 17:32:56 by ageels        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef DISPLAY_H
# define DISPLAY_H

# include "../../minishell.h"

# define PROMPT " (⁠╯⁠°⁠□⁠°⁠）⁠╯⁠︵⁠ ⁠┻⁠━⁠┻ "

void	handle_sigint(int sig);
void	setup_termios(void);
void	catch_signals(void);
void	heredoc_signals(void);
void	default_signals(void);
void	ignore_signals(void);
void	catch_errno(int err);

#endif