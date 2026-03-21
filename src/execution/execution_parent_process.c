/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_parent_process.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asando <asando@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/07 11:35:13 by asando            #+#    #+#             */
/*   Updated: 2026/03/21 19:11:44 by asando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

static int	ft_wait_children_process(pid_t *pids, int n_cmd)
{
	int	status;
	int	last_process_status;
	int	i;

	i = 0;
	status = 0;
	last_process_status = 0;
	while (i < n_cmd)
	{
		waitpid(pids[i], &status, 0);
		if (i == n_cmd - 1)
			last_process_status = status;
		i++;
	}
	return (last_process_status);
}

static int	ft_get_exit_status(int exit_status)
{
	if (WIFEXITED(exit_status))
		return (WEXITSTATUS(exit_status));
	if (WIFSIGNALED(exit_status))
		return (128 + WTERMSIG(exit_status));
	return (1);
}

void	ft_parent_process(t_shell *shell, int **pipes, pid_t *pids, int n_cmd)
{
	int	status;

	ft_close_pipes(n_cmd - 1, pipes);
	status = ft_wait_children_process(pids, n_cmd);
	shell->exit_status = ft_get_exit_status(status);
	return ;
}
