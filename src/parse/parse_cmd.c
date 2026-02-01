/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asando <asando@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/25 13:15:15 by asando            #+#    #+#             */
/*   Updated: 2026/02/01 19:33:46 by asando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

t_cmd	*ft_new_cmd(void)
{
	t_cmd	*new_cmd;

	new_cmd = malloc(sizeof(t_cmd));
	if (new_cmd == NULL)
		return (NULL);
	new_cmd->args = NULL;
	new_cmd->redirs = NULL;
	new_cmd->next_cmd = NULL;
	return (new_cmd);
}

t_redir	*ft_new_redir(t_token_type type, char *filename)
{
	t_redir	*new_redir;

	new_redir = malloc(sizeof(t_redir));
	if (new_redir == NULL)
		return (NULL);
	new_redir->type = type;
	new_redir->filename = ft_strdup(filename);
	new_redir->next_redir = NULL;
	return (new_redir);
}

//NOTE: consider to clean value
int	ft_add_arg(t_cmd *cmd, char *value)
{
	int		count;
	int		i;
	char	**new_arg;

	count = 0;
	i = 0;
	if (cmd->args)
	{
		while (cmd->args[count])
			count++;
	}
	new_arg = malloc(sizeof(char *) * (count + 2));
	if (new_arg == NULL)
		return (-1);
	while (cmd->args && cmd->args[i])
	{
		new_arg[i] = ft_strdup(cmd->args[i]);
		i++;
	}
	new_arg[i] = ft_strdup(value);
	new_arg[i + 1] = NULL;
	ft_free_args(cmd->args);
	cmd->args = new_arg;
	return (0);
}

int	ft_add_redir(t_cmd *cmd, t_token_type type, char *filename)
{
	t_redir	*new_redir;
	t_redir	*tmp;

	new_redir = ft_new_redir(type, filename);
	if (new_redir == NULL)
		return (-1);
	if (cmd->redirs == NULL)
	{
		cmd->redirs = new_redir;
		return (0);
	}
	tmp = cmd->redirs;
	while (tmp->next_redir)
		tmp = tmp->next_redir;
	tmp = new_redir;
	return (0);
}

void	ft_add_cmd(t_cmd **pipeline, t_cmd *new_cmd)
{
	t_cmd	*tmp;

	tmp = *pipeline;
	if (*pipeline == NULL)
	{
		*pipeline = new_cmd;
		return ;
	}
	while (tmp->next_cmd)
		tmp = tmp->next_cmd;
	tmp->next_cmd = new_cmd;
	return ;
}
