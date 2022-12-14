/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   structs.h                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: ageels <ageels@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/26 20:32:32 by ageels        #+#    #+#                 */
/*   Updated: 2022/10/31 19:08:17 by ageels        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

enum	e_token_type {
	WORD = 1,
	GREAT = 2,
	LESS = 4,
	PIPE = 8,
	GREATGREAT = 16,
	LESSLESS = 32,
	DOLL = 64,
	DOLLQ = 128,
	QUOT = 256,
	DQUOT = 512,
	WSPACE = 1024
};

typedef struct s_token {
	enum e_token_type	type;
	char				*data;
	struct s_token		*next;
}	t_token;

typedef struct s_str_list
{
	char				*str;
	int					append_mode;
	struct s_str_list	*next;
}	t_str_list;

typedef struct s_simple {
	char			**argv;
	int				argc;
	char			*bin;
	t_str_list		*outfiles;
	t_str_list		*infiles;
	struct s_simple	*next;
}	t_simple;

typedef struct s_doc {
	enum e_token_type	type;
	char				*name;
	int					fd;
	char				*eof;
	struct s_doc		*next;
}	t_doc;

typedef struct s_cmd {
	char			**envc;
	char			**paths;
	int				cmd_count;
	t_token			*tokens;
	t_simple		*simples;
	t_doc			*doc;
	unsigned int	err;
}	t_cmd;

#endif
