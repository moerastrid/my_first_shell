#ifndef STRUCTS_H
# define STRUCTS_H

enum	e_token_type {
	WORD = 0,
	GREAT = 1,
	LESS = 2,
	PIPE = 3,
	GREATGREAT = 4,
	LESSLESS = 5,
	DOLL = 6,
	DOLLQ = 7,
	QUOT = 8,
	DQUOT = 9,
	WSPACE = 10
};

typedef struct s_token {
	enum e_token_type	type;
	char				*data;
	struct s_token		*next;
}	t_token;

typedef struct s_simple {
	char			**argv;
	int				argc;
	char			*bin;
	struct s_simple	*next;
}	t_simple;

typedef struct s_str_list
{
	char				*str;
	int					append_mode;
	struct s_str_list	*next;
}	t_str_list;

typedef struct s_cmd {
	char		**envc;
	char		**paths;
	int			cmd_count;
	t_token		*tokens;
	t_simple	*simples;
	t_str_list	*outfiles;
	t_str_list	*infiles;
	t_str_list	*delimiters;
}	t_cmd;

#endif

// ==39144== TO DEBUG THIS PROCESS USING GDB: start GDB like this
// ==39144==   /path/to/gdb ./minishell
// target remote | /usr/lib/x86_64-linux-gnu/valgrind/../../bin/vgdb --pid=39144