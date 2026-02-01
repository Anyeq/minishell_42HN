/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_free_function.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asando <asando@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 17:34:05 by asando            #+#    #+#             */
/*   Updated: 2026/02/01 17:02:25 by asando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

void	ft_free_args(char **args)
{
	int		i;

	i = 0;
	if (args == NULL)
		return ;
	while (args[i])
	{
		free(args[i]);
		i++;
	}
	free(args);
	return ;
}

void	ft_free_redirs(t_redir **redirs)
{
	t_redir	*tmp;
	t_redir	*to_del;

	tmp = *redirs;
	to_del = tmp;
	while (tmp)
	{
		tmp = tmp->next_redir;
		free(to_del);
		to_del = tmp;
	}
	*redirs = NULL;
	return ;
}

void	ft_free_cmd(t_cmd *cmd)
{
	ft_free_args(cmd->args);
	ft_free_redirs(&cmd->redirs);
	return ;
}

void	ft_free_pipeline(t_cmd **cmd)
{
	t_cmd	*tmp;
	t_cmd	*to_del;

	tmp = *cmd;
	to_del = tmp;
	while (tmp)
	{
		tmp = tmp->next_cmd;
		ft_free_cmd(to_del);
		free(to_del);
		to_del = tmp;
	}
	*cmd = NULL;
	return ;
}
