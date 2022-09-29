/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnuyten <tnuyten@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 16:07:28 by tnuyten           #+#    #+#             */
/*   Updated: 2022/09/29 16:07:44 by tnuyten          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_H
# define TOKEN_H

enum	 e_token_type {
	WORD = 0,
	GREAT = 1,
	LESS = 2,
	PIPE = 3,
	GREATGREAT = 4,
	LESSLESS = 5,
	DOLL = 6,
	DOLLQ = 7,
};

typedef struct s_token {
	enum e_token_type	type;
	char				*data;
	struct s_token		*next;
}	t_token;

void	token_add_back(t_token *tokens, t_token *new);
t_token	*token_new(char *data, int type);
void	merge_token_with_next(t_token *token);
int		token_length(t_token *token);
void	free_token(t_token *token);
void	free_token_list(t_token *token);

#endif
