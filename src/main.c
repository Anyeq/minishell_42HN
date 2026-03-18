/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asando <asando@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/18 19:26:20 by asando            #+#    #+#             */
/*   Updated: 2026/03/18 19:20:12 by asando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	*g_exit_status;

int	main(int argc, char **argv, char **envp)
{
	t_shell	shell;

	(void)argc;
	(void)argv;
	if (ft_shell_init(&shell, envp) == -1)
		return (1);
	g_exit_status = &(shell.exit_status);
	shell_loop(&shell);
	ft_shell_destroy(&shell);
	return (0);
}
