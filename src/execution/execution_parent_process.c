/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_parent_process.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asando <asando@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/07 11:35:13 by asando            #+#    #+#             */
/*   Updated: 2026/02/07 12:09:05 by asando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

// OPTIMIZE: Potentially unused one out of two int variable
int	ft_wait_childrenn_process(pid_t *pids, int n_cmd)
{
	int	status;
	int	last_process_status;

	status = 0;
	last_process_status = 0;
	while (i < n_cmd)
	{
		waitpid(pids[i], &status, 0);
		if (i == n_cmd - 1)
			last_process_status = status;
		i++;
	}
	return (last_process_Status);
}

int	fd_get_exit_status(int exit_status)
{
	if (WIFEXITED(exit_status))
		return (WEXITSTATUS(exit_status));
	if (WIFSIGNALED(exit_status))
		return (128 + WTERMSIG(exit_status));
	return (1);
}

int	ft_parent_process(int **pipes, pid_t *pids, int	n_cmd)
{
	int	status;
	int exit_code;


}
