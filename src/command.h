/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnuyten <tnuyten@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 13:48:05 by tnuyten           #+#    #+#             */
/*   Updated: 2022/09/26 14:19:24 by tnuyten          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

typedef struct s_SimpleCommand {
		int numberOfAvailableArguments;
		int numberOfArguments;
		char **arguments;
} t_simple;

typedef struct s_Command {
		int numberOfAvailableSimpleCommands;
		int numberOfSimpleCommands;
		struct SimpleCommand **simpleCommands;
		char *outFile;
		char *inputFile;
		char *errFile;
} t_cmd;