/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asando <asando@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/18 19:26:20 by asando            #+#    #+#             */
/*   Updated: 2026/02/25 09:02:55 by asando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//NOTE: Global variable for exit status

int	g_exit_status = 0;

int	main(int argc, char **argv, char **envp)
{
	char		*line;
	t_token		*tokens;
	t_cmd		*cmds;
	t_helper	helper;

	(void)argc;
	(void)argv;
	helper.envp = ft_copy_envp(envp);
	if (helper.envp == NULL)
	{
		perror("malloc error");
		return (NULL);
	}
	minishell_loop(&helper);
	free(helper.envp);
	return (0);
}
