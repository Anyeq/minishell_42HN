/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_executor.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asando <asando@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/07 19:10:55 by asando            #+#    #+#             */
/*   Updated: 2026/02/08 12:55:35 by asando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

static int	**ft_create_pipe(int n_cmd, t_cmd **pipeline)
{
	int	**pipes;

	pipes == NULL;
	if (n_cmd > 1)
	{
		pipes = ft_create_pipe(n_cmd);
		if (pipes == NULL)
			ft_free_pipeline(pipeline);
	}
	return (pipes);
}

void	ft_executor(t_cmd **pipeline)
{
	int		n_cmd;
	int		**pipes;
	pid_t	*pids;
	int		fork_status;

	fork_status = 0;
	n_cmd = ft_cmd_count(*pipeline);
	pipes = NULL;
	pids = malloc(sizeof(pid_t) * n_cmd);
	if (pids == NULL)
	{
		ft_free_pipeline(pipeline);
		return ;
	}
	pipes = ft_if_multiple_cmd(n_cmd, pipeline);
	if (pipes == NULL)
		return ;
	fork_status = ft_create_child_process(*pipeline, n_cmd, pids, pipes);
	if (fork_status == 0)
		ft_parent_process(pipes, pids, n_cmd);
	ft_clean_pipe_allocation(n_cmd - 1, pipes);
	free(pids);
}
