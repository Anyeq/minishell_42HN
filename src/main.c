/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asando <asando@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/18 19:26:20 by asando            #+#    #+#             */
/*   Updated: 2026/03/22 15:20:32 by asando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	*g_exit_status;

static void	print_banner(void)
{
	printf("\n\n");
	printf("\033[1;36m");
	printf("███╗   ███╗██╗███╗   ██╗██╗███████╗██╗  ██╗\n");
	printf("████╗ ████║██║████╗  ██║██║██╔════╝██║  ██║\n");
	printf("██╔████╔██║██║██╔██╗ ██║██║███████╗███████║\n");
	printf("██║╚██╔╝██║██║██║╚██╗██║██║╚════██║██╔══██║\n");
	printf("██║ ╚═╝ ██║██║██║ ╚████║██║███████║██║  ██║\n");
	printf("╚═╝     ╚═╝╚═╝╚═╝  ╚═══╝╚═╝╚══════╝╚═╝  ╚═╝\n");
	printf("\033[0m");
	printf("\n\n");
}

int	main(int argc, char **argv, char **envp)
{
	t_shell	shell;

	(void)argc;
	(void)argv;
	print_banner();
	if (ft_shell_init(&shell, envp) == -1)
		return (1);
	g_exit_status = &(shell.exit_status);
	shell_loop(&shell);
	ft_shell_destroy(&shell);
	return (shell.exit_status);
}
