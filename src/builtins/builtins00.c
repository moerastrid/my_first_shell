/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtins00.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: ageels <ageels@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/12 14:12:13 by ageels        #+#    #+#                 */
/*   Updated: 2022/09/29 17:42:12 by ageels        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	bi_echo(void);
void	bi_cd(void);
void	bi_pwd(void);
void	bi_export(void);
void	bi_unset(void);
void	bi_env(void);
void	bi_exit(void);