/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_executor.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asando <asando@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/07 19:10:55 by asando            #+#    #+#             */
/*   Updated: 2026/03/18 18:38:08 by asando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

static int	**ft_create_pipe(int n_cmd)
{
	int	**pipes;

	pipes = ft_init_pipe(n_cmd);
	return (pipes);
}

static int	ft_init_variable(int *fork_s, int ***pipes, t_shell *shell,
				pid_t **pids)
{
	*fork_s = 0;
	*pipes = NULL;
	*pids = malloc(sizeof(pid_t) * shell->n_cmd);
	if (pids == NULL)
	{
		perror("minishell: malloc error");
		return (-1);
	}
	return (0);
}

void	ft_executor(t_shell *shell)
{
	int		**pipes;
	pid_t	*pids;
	int		fork_status;

	shell->n_cmd = ft_cmd_count(shell->cmds);
	if (ft_init_variable(&fork_status, &pipes, shell, &pids) == -1)
		return ;
	if (shell->n_cmd > 1)
	{
		pipes = ft_create_pipe(shell->n_cmd);
		if (pipes == NULL)
		{
			free(pids);
			return ;
		}
	}
	fork_status = ft_create_child_process(shell, pids, pipes);
	if (fork_status == 0)
		ft_parent_process(shell, pipes, pids, shell->n_cmd);
	ft_clean_pipe_allocation(shell->n_cmd - 1, pipes);
	free(pids);
	return ;
}
