/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_executor.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asando <asando@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/07 19:10:55 by asando            #+#    #+#             */
/*   Updated: 2026/02/13 11:16:11 by asando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

static int	**ft_create_pipe(int n_cmd, t_cmd **pipeline)
{
	int	**pipes;

	pipes == NULL;
	if (n_cmd > 1)
	{
		pipes = ft_init_pipe(n_cmd);
		if (pipes == NULL)
			ft_free_pipeline(pipeline);
	}
	return (pipes);
}

//TODO: Push it outside the executor
t_helper	*ft_init_helper(t_cmd **pipeline, char **envp)
{
	t_helper	*helper;

	helper = malloc(sizeof(t_helper));
	helper->n_cmd = ft_cmd_count(*pipeline);
	helper->envp = envp;
}

//TODO: add struct or add more parameter on ft_Executor to pass copy of env
//TODO: Clean pipeline outside ft_executor
void	ft_executor(t_cmd **pipeline, t_helper *helper)
{
	int		n_cmd;
	int		**pipes;
	pid_t	*pids;
	int		fork_status;

	fork_status = 0;
	pipes = NULL;
	pids = malloc(sizeof(pid_t) * helper->n_cmd);
	if (pids == NULL)
	{
		perror("malloc error");
		ft_free_pipeline(pipeline);
		return ;
	}
	pipes = ft_create_pipe(helper->n_cmd, pipeline);
	if (pipes == NULL)
		return ;
	fork_status = ft_create_child_process(*pipeline, helper, pids, pipes);
	if (fork_status == 0)
		ft_parent_process(pipes, pids, helper->n_cmd);
	ft_clean_pipe_allocation(helper->n_cmd - 1, pipes);
	free(pids);
}
