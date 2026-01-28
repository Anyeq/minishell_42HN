/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asando <asando@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/25 13:15:15 by asando            #+#    #+#             */
/*   Updated: 2026/01/28 21:06:31 by asando           ###   ########.fr       */
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
	new_cmd->args = NULL;
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
		return ;
	while (cmd->args[i])
	{
		new_arg[i] = cmd->args[i];
		i++;
	}
	new_arg[i] = value;
	new_arg[i + 1] = NULL;
	ft_free_args(cmd->args);
	cmd->args = new_arg;
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

t_cmd	*parse_loop(t_token *tokens)
{
	t_cmd	*pipeline;
	t_cmd	*curr_cmd;

	curr_cmd = NULL;
	while (tokens)
	{
		if (curr_cmd == NULL)
			curr_cmd = ft_new_cmd();
		
	}
	return (pipeline);
}
