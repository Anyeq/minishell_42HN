/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_pipe.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asando <asando@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/07 19:15:32 by asando            #+#    #+#             */
/*   Updated: 2026/02/07 19:16:43 by asando           ###   ########.fr       */
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
		perror("malloc error");
		return (NULL);
	}
	while (i < n_cmd - 1)
	{
		pipes[i] = malloc(sizeof(int) * 2);
		if (pipes[i] == NULL)
		{
			perror("malloc error");
			ft_clean_pipe_allocation(i, pipes);
			free(pipes);
			return (NULL);
		}
		i++;
	}
	return (pipes);
}

//NOTE: when pipe error should close the rest
//NOTE: when NULL should clean everything
int	**ft_create_pipe(int n_cmd)
{
	int	i;
	int	**pipes;

	i = 0;
	pipes = ft_allocate_pipes(n_cmd);
	if (pipes == NULL)
		return (NULL);
	while (i < n_cmd)
	{
		if (pipe(pipes[i]) == -1)
		{
			perror("pipe error");
			ft_close_pipes(i, pipes);
			ft_clean_pipe_allocation(i, pipes);
			free(pipes);
			return (NULL);
		}
		i++;
	}
	return (pipes);
}
