/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asando <asando@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/18 19:26:20 by asando            #+#    #+#             */
/*   Updated: 2026/03/16 22:35:34 by asando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_exit_status = 0;

int	main(int argc, char **argv, char **envp)
{
	t_helper	helper;

	(void)argc;
	(void)argv;
	helper.env_list = ft_init_env(envp);
	if (helper.env_list == NULL)
	{
		perror("minishell: malloc error");
		return (-1);
	}
	minishell_loop(&helper);
	free(helper.env_list);
	return (0);
}
