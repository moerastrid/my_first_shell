/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   token.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: tnuyten <tnuyten@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/29 16:07:28 by tnuyten       #+#    #+#                 */
/*   Updated: 2022/10/26 19:14:26 by ageels        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_H
# define TOKEN_H

# include "../../minishell.h"

// lexer.c
int		is_token_char(char *str);
int		token_type(char *str);
int		token_length(t_token *token);

//tokenize.c
int		tokenize(t_cmd *cmd, char *input);
int		lessless_length(char *input);
void	token_delete_empty_subs(t_token **tokens);

//token_length.c
int		word_length(char *input);
int		quot_length(char *input);
int		dquot_length(char *input);
int		doll_length(char *input);

// token_free.c
void	free_token(t_token *token);
void	free_token_list(t_token *token);

// token.c
void	token_add_back(t_token **root, t_token *new);
t_token	*token_new(char *data, int type);
void	merge_words(t_token *token);
void	remove_token_from_list(t_token **root, t_token *token);

#endif