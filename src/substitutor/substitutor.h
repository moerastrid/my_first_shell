/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   substitutor.h                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: ageels <ageels@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/21 22:32:19 by ageels        #+#    #+#                 */
/*   Updated: 2022/10/21 22:32:20 by ageels        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef SUBSTITUTOR_H
# define SUBSTITUTOR_H

# include "../../minishell.h"

char	*get_envp_var(char *str, char **envp);
void	substitute_dquot(t_token *token, char **envp);

#endif