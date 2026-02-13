/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_child_process.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asando <asando@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/06 19:05:48 by asando            #+#    #+#             */
/*   Updated: 2026/02/13 08:45:03 by asando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

static void	ft_child_process(t_cmd *cmd, int i, int n_cmd, int **pipes)
{
	int	n;

	n = 0;
	if (i > 0)
		dup2(pipes[i - 1][0], STDIN_FILENO);
	if (i < (n_cmd - 1))
		dup2(pipes[i][1], STDOUT_FILENO);
	while (n < n_cmd - 1)
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
	// BUG: one parameter missing envp variable
	execve(ft_find_path(cmd->args[0]), cmd->args, );
	perror("execve error");
	exit(1);
}

//BUG: working on eleminating n_cmd on parameter so we can put envp
static void	ft_child_process_fail(char *cmd, int **pipes, int *pids, int i)
{
	int	n;

	n = 0;
	ft_close_pipes(n_cmd - 1, pipes);
	while (n < i)
	{
		waitpid(pids[n], NULL, 0);
		n++;
	}
	// TODO: Maybe we have to add it to global variable here
	return ;
}

int	ft_create_child_process(t_cmd *cmd, char **envp, int *pids, int **pipes)
{
	int	i;
	int	n_cmd;

	i = 0;
	n_cmd = ft_cmd_count(cmd);
	while (i < n_cmd)
	{
		pids[i] = fork();
		if (pids[i] == -1)
		{
			perror("fork");
			ft_child_process_fail(envp, pipes, pids, i);
			return (-1) ;
		}
		if (pids[i] == 0)
			ft_child_process(cmd, i, envp, pipes);
		cmd = cmd->next_cmd;
		i++;
	}
	return (0);
}
