/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   token.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: tnuyten <tnuyten@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/29 16:07:28 by tnuyten       #+#    #+#                 */
/*   Updated: 2022/10/14 14:36:20 by ageels        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_H
# define TOKEN_H

# include "../../lib/libft/libft.h"
# include "../../structs.h"

void	token_add_back(t_token *tokens, t_token *new);
t_token	*token_new(char *data, int type);
void	merge_token_with_next(t_token *token);
void	merge_redirects(t_token *token);
void	free_token(t_token *token);
void	free_token_list(t_token *token);
t_token	*tokenize(char *input);
void	print_tokens(t_token *root);

//length fun
int		is_token_char(char *str);
int		token_type(char *str);
int		token_length(t_token *token);
int		word_length(char *input);
int		quot_length(char *input);
int		dquot_length(char *input);

#endif
