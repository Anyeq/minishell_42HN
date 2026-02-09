/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_child_process.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asando <asando@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/06 19:05:48 by asando            #+#    #+#             */
/*   Updated: 2026/02/09 14:50:11 by asando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

char	*ft_strjoin3(char *str1, char *str2, char *str3)
{
	char	*tmp;
	char	*res;

	tmp = ft_strjoin(str1, str2);
	if (tmp == NULL)
	{
		perror("malloc error");
		return (NULL);
	}
	res = ft_strjoin(tmp, res);
	if (res == NULL)
		perror("malloc error");
	free (tmp);
	return (res);
}

void	ft_free_split(char **list_str)
{
	int	i;

	i = 0;
	while (list_str[i])
	{
		free(list_str[i]);
		i++;
	}
	free(list_str);
	return ;
}

//NOTE: paths null == clean path_env
char	*ft_find_path(char *path)
{
	char	*path_env;
	char	**paths;
	char	*full;
	int		i;

	i = 0;
	if (ft_strchr(path, '/'))
		return (ft_strdup(path));
	path_env = getenv("PATH");
	if (path_env == NULL)
		return (NULL);
	paths = ft_split(path_env, ':');
	if (paths == NULL)
		return (NULL);
	while (paths[i])
	{
		full = ft_strjoin3(paths[i], "/", path);
		if (access(full, X_OK) == 0)
		{
			ft_free_split(paths);
			return (full);
		}
		free(full);
		i++;
	}
	ft_free_split(paths);
	return (NULL);
}

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
	execve(find_path(cmd->args[0]), );
	perror("execve error");
	exit(1);
}

static void	ft_child_process_fail(t_cmd *cmd, int **pipes, int *pids, int i)
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

int	ft_create_child_process(t_cmd *cmd, int n_cmd, int *pids, int **pipes)
{
	int	i;

	i = 0;
	while (i < n_cmd)
	{
		pids[i] = fork();
		if (pids[i] == -1)
		{
			perror("fork");
			ft_child_process_fail(n_cmd, pipes, pids, i);
			return (-1) ;
		}
		if (pids[i] == 0)
			ft_child_process(cmd, i, n_cmd, pipes);
		cmd = cmd->next_cmd;
		i++;
	}
	return (0);
}
