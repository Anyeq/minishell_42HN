/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asando <asando@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/25 13:15:15 by asando            #+#    #+#             */
/*   Updated: 2026/01/25 16:58:40 by asando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

t_cmd	*ft_new_cmd(void)
{
	t_cmd	*new_cmd;

	new_cmd = malloc(sizeof(t_cmd));
	//NOTE: Probably need to throw error because it's failed here
	if (new_cmd == NULL)
		return (NULL);
	new_cmd->argv = NULL;
	new_cmd->redirs = NULL;
	new_cmd->next_cmd = NULL;
	return (new_cmd);
}

t_redir	*ft_new_redir(t_token_type type, char *filename)
{
	t_redir	*new_redir;

	new_redir = malloc(sizeof(t_redir));
	//NOTE: Probably need to throw error because it's failed here
	if (new_redir == NULL)
		return (NULL);
	new_redir->type = type;
	new_redir->filename = filename;
	new_redir->next_redir = NULL;
	return (new_redir);
}

//NOTE: Error when failed need to be considered
void	ft_add_arg(t_cmd *cmd, char *value)
{
	int		count;
	int		i;
	char	**new_argv;

	count = 0;
	i = 0;
	if (cmd->argv)
	{
		while (cmd->argv[count])
			count++;
	}
	new_argv = malloc(sizeof(char *) * (count + 2));
	if (new_argv == NULL)
		return ;
	while (cmd->argv[i])
	{
		new_argv[i] = cmd->argv[i];
		i++;
	}
	new_argv[i] = value;
	new_argv[i + 1] = NULL;
	//BUG: Free the cmd->argv
	cmd->argv = new_argv;
	return ;
}

void	ft_add_redir(t_cmd *cmd, t_token_type type, char *filename)
{
	t_redir	*new_redir;
	t_redir	*tmp;

	new_redir = ft_new_redir(type, filename);
	if (cmd->redirs == NULL)
	{
		cmd->redirs = new_redir;
		return ;
	}
	tmp = cmd->redirs;
	while (tmp->next_redir)
		tmp = tmp->next_redir;
	tmp = new_redir;
	return ;
}
