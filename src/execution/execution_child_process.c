/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_child_process.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asando <asando@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/06 19:05:48 by asando            #+#    #+#             */
/*   Updated: 2026/03/14 20:54:27 by asando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

static void	ft_prepare_pipe(int **pipes, int i, t_helper *helper)
{
	int		n;

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
	return ;
}

static void	ft_child_process(t_cmd *cmd, int i, t_helper *helper, int **pipes)
{
	char	**envp;

	ft_prepare_pipe(pipes, i, helper);
	envp = ft_create_envp(helper->env);
	if (envp == NULL)
		exit(1);
	ft_redirection_function(cmd->redirs);
	if (ft_is_builtin(cmd->args[0]))
	{
		ft_exec_builtin(cmd->args, envp);
		exit(0);
	}
	execve(ft_find_path(cmd->args[0]), cmd->args, envp);
	perror("minishell: execve error");
	exit(1);
}

static void	ft_child_process_failed(t_helper *helper, int **pipes, int *pids,
				int i)
{
	int	n;

	n = 0;
	ft_close_pipes(helper->n_cmd - 1, pipes);
	while (n < i)
	{
		waitpid(pids[n], NULL, 0);
		n++;
	}
	g_exit_status = 1;
	return ;
}

int	ft_create_child_process(t_cmd *cmd, t_helper *helper, int *pids,
				int **pipes)
{
	int	i;

	i = 0;
	while (i < helper->n_cmd)
	{
		pids[i] = fork();
		if (pids[i] == -1)
		{
			perror("minishell: fork error");
			ft_child_process_failed(helper, pipes, pids, i);
			return (-1);
		}
		if (pids[i] == 0)
		{
			ft_setup_signals_child(void);
			ft_child_process(cmd, i, helper, pipes);
		}
		cmd = cmd->next_cmd;
		i++;
	}
	return (0);
}
