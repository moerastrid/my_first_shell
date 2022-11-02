/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   display.h                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: ageels <ageels@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/30 16:27:35 by ageels        #+#    #+#                 */
/*   Updated: 2022/11/02 15:04:47 by ageels        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef DISPLAY_H
# define DISPLAY_H

# include "../../minishell.h"

# define PROMPT " (⁠╯⁠°⁠□⁠°⁠）⁠╯⁠︵⁠ ⁠┻⁠━⁠┻ "

//signals.c 
void	handle_sigint(int sig);
void	catch_signals(void);
void	heredoc_signals(void);
void	default_signals(void);

//prompt.c (last of signals)
void	ignore_signals(void);

//errors.c
void	catch_errno(t_cmd cmd);

#endif