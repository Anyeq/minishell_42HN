/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asando <asando@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/18 19:26:20 by asando            #+#    #+#             */
/*   Updated: 2026/03/16 19:12:16 by asando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_exit_status = 0;

int	main(int argc, char **argv, char **envp)
{
	t_helper	helper;

	(void)argc;
	(void)argv;
	helper.envp = ft_init_env_list(envp);
	if (helper.envp == NULL)
	{
		perror("minishell: malloc error");
		return (NULL);
	}
	minishell_loop(&helper);
	free(helper.envp);
	return (0);
}
