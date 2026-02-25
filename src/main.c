/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asando <asando@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/18 19:26:20 by asando            #+#    #+#             */
/*   Updated: 2026/02/25 08:13:34 by asando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//NOTE: Global variable for exit status
int	main(int argc, char **argv, char **envp)
{
	char	*line;
	t_token	*tokens;
	t_cmd	*cmds;
	char	**envp_copy;

	(void)argc;
	(void)argv;
	// TODO: read
	// TODO: Creat token
	// TODO: create pipeline --> if error here token has to be cleaned
	// TODO: remove token
	// TODO: executor --> pipeline cleaned here
	// TODO: Repeat
	return ;
}
