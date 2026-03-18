/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signalmnshell.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asando <asando@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 15:27:16 by asando            #+#    #+#             */
/*   Updated: 2026/03/18 19:20:02 by asando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNALMNSHELL_H
# define SIGNALMNSHELL_H

# include <signal.h>
# include <unistd.h>
# include <stdio.h>
# include "expansion.h"
# include <readline/readline.h>
# include <readline/history.h>

extern int	*g_exit_status;

void	ft_setup_signals_shell(void);
void	ft_setup_signals_heredoc(void);
void	ft_setup_signals_child(void);

#endif
