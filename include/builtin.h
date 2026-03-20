/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eynaksho <eynaksho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 13:53:57 by asando            #+#    #+#             */
/*   Updated: 2026/03/20 21:18:12 by eynaksho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include "libft.h"
# include "env.h"
# include "parse.h"

int	builtin_cd(t_cmd *cmd, t_shell *shell);
int	builtin_unset(t_cmd *cmd, t_shell *shell);
int	builtin_pwd(void);
int	builtin_export(t_cmd *cmd, t_shell *shell);
int	builtin_echo(t_cmd *cmd);
int	builtin_env(t_shell *shell);
int	ft_is_builtin(char *cmd);
int	ft_exec_builtin(t_cmd *cmd, t_shell *shell);
int	builtin_exit(t_cmd *cmd, t_shell *shell);

#endif
