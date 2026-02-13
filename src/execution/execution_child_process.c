/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_child_process.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asando <asando@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/06 19:05:48 by asando            #+#    #+#             */
/*   Updated: 2026/02/13 11:37:12 by asando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

static void	ft_child_process(t_cmd *cmd, int i, t_helper *helper, int **pipes)
{
	int	n;

	n = 0;
	if (i > 0)
		dup2(pipes[i - 1][0], STDIN_FILENO);
	if (i < (helper->n_cmd - 1))
		dup2(pipes[i][1], STDOUT_FILENO);
	while (n < helper->n_cmd - 1)
	{
		close(pipes[n][0]);
		close(pipes[n][1]);
		n++;
	}
	ft_redirection_function(cmd->redirs);
	// NOTE: Waiting for the real buildint interface
	if (ft_is_buildint(cmd->args[0]))
	{
		ft_run_buildint(cmd->args[0]);
		exit(0);
	}
	execve(ft_find_path(cmd->args[0]), cmd->args, helper->envp);
	perror("execve error");
	exit(1);
}

static void	ft_child_process_failed(t_helper *helper, int **pipes, int *pids, int i)
{
	int	n;

	n = 0;
	ft_close_pipes(helper->n_cmd - 1, pipes);
	while (n < i)
	{
		waitpid(pids[n], NULL, 0);
		n++;
	}
	// TODO: Maybe we have to add it to global variable here
	return ;
}

int	ft_create_child_process(t_cmd *cmd, t_helper *helper, int *pids, int **pipes)
{
	int	i;

	i = 0;
	while (i < helper->n_cmd)
	{
		pids[i] = fork();
		if (pids[i] == -1)
		{
			perror("fork error");
			ft_child_process_failed(helper, pipes, pids, i);
			return (-1) ;
		}
		if (pids[i] == 0)
			ft_child_process(cmd, i, helper, pipes);
		cmd = cmd->next_cmd;
		i++;
	}
	return (0);
}
