/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asando <asando@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 13:16:37 by asando            #+#    #+#             */
/*   Updated: 2026/02/25 15:30:47 by asando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "signalmnshell.h"

void	ft_sigint_handler_shell(int sig)
{
	(void)sig;
	g_exit_status = 130;
	write(STDOUT_FILENO, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	ft_sigint_handler_heredoc(int sig)
{
	(void)sig;
	g_exit_status = 130;
	write(STDOUT_FILENO, "\n", 1);
}

void	ft_setup_signals_shell(void)
{
	signal(SIGINT, ft_sigint_handler_shell);
	signal(SIGQUIT, SIG_IGN);
}

void	ft_setup_signals_heredoc(void)
{
	signal(SIGINT, ft_sigint_handler_heredoc);
	signal(SIGQUIT, SIG_IGN);
}

void	ft_setup_signals_child(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}
