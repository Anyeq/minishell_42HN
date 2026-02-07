/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_process_utils.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asando <asando@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/06 17:25:06 by asando            #+#    #+#             */
/*   Updated: 2026/02/07 19:20:58 by asando           ###   ########.fr       */
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

void	ft_clean_pipe_allocation(int n, int **address)
{
	int	i;

	i = 0;
	if (address == NULL)
		return ;
	while (i < n)
	{
		free(address[i]);
		i++;
	}
	return ;
}

void	ft_close_pipes(int n, int **pipes)
{
	int	i;

	i = 0;
	if (pipes == NULL)
		return ;
	while (i < n)
	{
		close(pipes[i]);
		i++;
	}
	return ;
}
