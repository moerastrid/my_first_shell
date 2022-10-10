/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnuyten <tnuyten@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 16:07:28 by tnuyten           #+#    #+#             */
/*   Updated: 2022/09/29 21:00:56 by tnuyten          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_H
# define TOKEN_H

#include "../../minishell.h"

void	token_add_back(t_token *tokens, t_token *new);
t_token	*token_new(char *data, int type);
void	merge_token_with_next(t_token *token);
void	merge_redirects(t_token *token);
void	free_token(t_token *token);
void	free_token_list(t_token *token);

#endif
