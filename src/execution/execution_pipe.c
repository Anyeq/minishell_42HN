/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_pipe.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asando <asando@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/07 19:15:32 by asando            #+#    #+#             */
/*   Updated: 2026/03/20 00:58:21 by asando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

static int	**ft_allocate_pipes(int n_cmd)
{
	int	**pipes;
	int	i;

	i = 0;
	pipes = malloc(sizeof(int *) * (n_cmd - 1));
	if (pipes == NULL)
	{
		perror("minishell: malloc error");
		return (NULL);
	}
	while (i < n_cmd - 1)
	{
		pipes[i] = malloc(sizeof(int) * 2);
		if (pipes[i] == NULL)
		{
			perror("minishell: malloc error");
			ft_clean_pipe_allocation(i, pipes);
			pipes = NULL;
			return (NULL);
		}
		i++;
	}
	return (pipes);
}

int	**ft_init_pipe(int n_cmd)
{
	int	i;
	int	**pipes;

	i = 0;
	pipes = ft_allocate_pipes(n_cmd);
	if (pipes == NULL)
		return (NULL);
	while (i < n_cmd - 1)
	{
		if (pipe(pipes[i]) == -1)
		{
			perror("minishell: pipe error");
			ft_close_pipes(i, pipes);
			ft_clean_pipe_allocation(i, pipes);
			pipes = NULL;
			return (NULL);
		}
		i++;
	}
	return (pipes);
}
