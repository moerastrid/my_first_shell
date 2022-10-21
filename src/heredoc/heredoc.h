/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   heredoc.h                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: ageels <ageels@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/21 16:16:08 by ageels        #+#    #+#                 */
/*   Updated: 2022/10/21 16:19:54 by ageels        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEREDOC_H
# define HEREDOC_H

#include "../../minishell.h"

typedef struct s_doc {
	char			*name;
	int				fd;
	char			*eof;
	struct s_doc	*next;
}	t_doc;

#endif