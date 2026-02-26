/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signalmnshell.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asando <asando@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 15:27:16 by asando            #+#    #+#             */
/*   Updated: 2026/02/25 15:30:41 by asando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNALMNSHELL_H
# define SIGNALMNSHELL_H

#include <signal.h>
#include <unistd.h>
#include <readline/readline.h>

void	ft_sigint_handler_shell(int sig);
void	ft_sigint_handler_heredoc(int sig);
void	ft_setup_signals_shell(void);
void	ft_setup_signals_heredoc(void);
void	ft_setup_signals_child(void);

#endif
