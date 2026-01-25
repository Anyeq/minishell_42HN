/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asando <asando@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/25 13:15:15 by asando            #+#    #+#             */
/*   Updated: 2026/01/25 15:30:11 by asando           ###   ########.fr       */
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

void	ft_add_cmd(){}
void	ft_add_redir(){}
