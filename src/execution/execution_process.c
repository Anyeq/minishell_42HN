/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_process.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asando <asando@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/06 17:25:06 by asando            #+#    #+#             */
/*   Updated: 2026/02/06 18:31:17 by asando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int	ft_cmd_count(t_cmd *cmd)
{
	int	res;

	res = 0;
	while (cmd)
	{
		res++;
		cmd = cmd->next_cmd;
	}
	return (res);
}

//NOTE: when pipe error should close the rest
void	ft_create_pipe(int *pipes, int n_cmd)
{
	int	i;

	i = 0;
	while (i < n_cmd)
	{
		if (pipe(pipes[i]) == -1)
		{
			perror("pipe error");
			exit(1);
		}
		i++;
	}
	return ;
}

//NOTE: Protect all dup
//NOTE: if ft_redirection can be failed
void	ft_child_process(t_cmd *cmd, int i, int n_cmd, int *pipes)
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
	//NOTE: here should be execution of buildint
	//NOTE: here should be execution of external program
	//NOTE: with EXECVE
	//NOTE: if EXECVE failed return exit(1)
}

//NOTE: check if after exit memory is cleaned
void	ft_run_child_process(t_cmd *cmd, int n_cmd, int *pids, int *pipes)
{
	int		i;

	i = 0;
	while (i < n_cmd - 1)
	{
		pids[i] = fork();
		if (pids[i] == -1)
		{
			perror("fork");
			exit(1);
		}
		if (pids[i] == 0)
			ft_child_process(cmd, i, n_cmd, pipes);
		cmd = cmd->next_cmd;
		i++;
	}
	return ;
}
