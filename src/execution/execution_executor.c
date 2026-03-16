/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_executor.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asando <asando@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/07 19:10:55 by asando            #+#    #+#             */
/*   Updated: 2026/03/16 22:54:03 by asando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

static int	**ft_create_pipe(int n_cmd)
{
	int	**pipes;

	pipes = ft_init_pipe(n_cmd);
	return (pipes);
}

static int	ft_init_variable(int *fork_s, int ***pipes, t_helper *helper,
				pid_t **pids)
{
	*fork_s = 0;
	*pipes = NULL;
	*pids = malloc(sizeof(pid_t) * helper->n_cmd);
	if (pids == NULL)
	{
		perror("minishell: malloc error");
		return (-1);
	}
	return (0);
}

void	ft_executor(t_cmd **pipeline, t_helper *helper)
{
	int		**pipes;
	pid_t	*pids;
	int		fork_status;

	helper->n_cmd = ft_cmd_count(*pipeline);
	if (ft_init_variable(&fork_status, &pipes, helper, &pids) == -1)
		return ;
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
