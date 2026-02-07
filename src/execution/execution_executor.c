/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_executor.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asando <asando@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/07 19:10:55 by asando            #+#    #+#             */
/*   Updated: 2026/02/07 20:55:00 by asando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

// WARN: after pids fail malloc, should clean all memorry allocation
// WARN: after pipes return NULL, should clean all memorry allocation
void	ft_executor(t_cmd **pipeline)
{
	int		n_cmd;
	int		**pipes;
	pid_t	*pids;
	int		child_fail;

	child_fail = 0;
	n_cmd = ft_cmd_count(*pipeline);
	pids = malloc(sizeof(pid_t) * n_cmd);
	pipes = NULL;
	if (pids == NULL)
	{
		ft_free_pipeline(pipeline);
		return ;
	}
	if (n_cmd > 1)
	{
		pipes = ft_create_pipe(n_cmd);
		if (pipes == NULL)
		{
			ft_free_pipeline(pipeline);
			return ;
		}
	}
	child_fail = ft_create_child_process(*pipeline, n_cmd, pids, pipes);
	if (child_fail == 0)
		ft_parent_process(pipes, pids, n_cmd);
	ft_clean_pipe_allocation(n_cmd - 1, pipes);
	free(pids);
}
