/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_executor.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asando <asando@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/07 19:10:55 by asando            #+#    #+#             */
/*   Updated: 2026/03/13 11:47:26 by asando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

static int	**ft_create_pipe(int n_cmd)
{
	int	**pipes;

	pipes = ft_init_pipe(n_cmd);
	return (pipes);
}

void	ft_executor(t_cmd **pipeline, t_helper *helper)
{
	int		n_cmd;
	int		**pipes;
	pid_t	*pids;
	int		fork_status;

	fork_status = 0;
	pipes = NULL;
	helper->n_cmd = ft_cmd_count(*pipeline);
	pids = malloc(sizeof(pid_t) * helper->n_cmd);
	if (pids == NULL)
	{
		perror("minishell: malloc error");
		return ;
	}
	if (helper->n_cmd > 1)
	{
		pipes = ft_create_pipe(helper->n_cmd);
		if (pipes == NULL)
		{
			free(pids);
			return ;
		}
	}
	fork_status = ft_create_child_process(*pipeline, helper, pids, pipes);
	if (fork_status == 0)
		ft_parent_process(pipes, pids, helper->n_cmd);
	ft_clean_pipe_allocation(helper->n_cmd - 1, pipes);
	free(pids);
	return ;
}
