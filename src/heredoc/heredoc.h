/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   heredoc.h                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: ageels <ageels@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/21 16:16:08 by ageels        #+#    #+#                 */
/*   Updated: 2022/10/24 14:52:34 by ageels        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEREDOC_H
# define HEREDOC_H

# include "../../minishell.h"
# include "../substitutor/substitutor.h"

void	docadd_back(t_doc **doc, t_doc *new_doc);
void	docs_free(t_doc *doc);
t_doc	*docnew(t_token *token, t_token *lessless);
char	*substitute_line(char *line, char **envp);

#endif