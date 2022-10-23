/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   heredoc.h                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: ageels <ageels@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/21 16:16:08 by ageels        #+#    #+#                 */
/*   Updated: 2022/10/21 22:04:29 by ageels        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEREDOC_H
# define HEREDOC_H

# include "../../minishell.h"

void	docadd_back(t_doc **doc, t_doc *new_doc);
void	docs_free(t_doc *doc);
t_doc	*docnew(char *eof, t_token *lessless);

#endif