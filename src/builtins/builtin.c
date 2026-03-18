/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eynaksho <eynaksho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/05 21:40:35 by eynaksho          #+#    #+#             */
/*   Updated: 2026/03/18 19:49:18 by asando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	ft_is_builtin(char *cmd)
{
	if (!cmd)
		return (0);
	if (ft_strncmp(cmd, "echo", 5) == 0)
		return (1);
	if (ft_strncmp(cmd, "cd", 3) == 0)
		return (1);
	if (ft_strncmp(cmd, "pwd", 4) == 0)
		return (1);
	if (ft_strncmp(cmd, "export", 7) == 0)
		return (1);
	if (ft_strncmp(cmd, "unset", 6) == 0)
		return (1);
	if (ft_strncmp(cmd, "env", 4) == 0)
		return (1);
	if (ft_strncmp(cmd, "exit", 5) == 0)
		return (1);
	return (0);
}

int	ft_exec_builtin(t_cmd *cmd, t_shell *shell)
{
	if (ft_strncmp(cmd->args[0], "echo", 5) == 0)
		return (builtin_echo(cmd));
	if (ft_strncmp(cmd->args[0], "cd", 3) == 0)
		return (builtin_cd(cmd, shell));
	if (ft_strncmp(cmd->args[0], "pwd", 4) == 0)
		return (builtin_pwd());
	if (ft_strncmp(cmd->args[0], "export", 7) == 0)
		return (builtin_export(cmd, shell));
	if (ft_strncmp(cmd->args[0], "unset", 6) == 0)
		return (builtin_unset(cmd, shell));
	if (ft_strncmp(cmd->args[0], "env", 4) == 0)
		return (builtin_env(shell));
	//if (ft_strncmp(cmd->args[0], "exit", 5) == 0)
	//	return (builtin_exit(cmd, shell));
	return (1);
}
