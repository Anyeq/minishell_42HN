/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asando <asando@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 19:19:36 by asando            #+#    #+#             */
/*   Updated: 2026/02/05 19:51:24 by asando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

//NOTE: is exit return the error of open
//NOTE: protect duplicate
static void	ft_redir_no_heredoc(t_token_type type)
{
	if (redirs->type == TOKEN_REDIR_IN)
	{
		fd = open(redirs->filename, O_RDONLY);
		if (fd == -1)
			exit(1);
		dup2(fd, STDIN_FILENO);
		close(fd);
	}
	else if (redirs->type == TOKEN_REDIR_OUT)
	{
		fd = open(redirs->filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd == -1)
			exit(1);
		dup2(fd, STDOUT_FILENO);
		close(fd);
	}
	else if (redirs->type == TOKEN_APPEND)
	{
		fd = open(redirs->filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (fd == -1)
			exit(1);
		dup2(fd, STDOUT_FILENO);
		close(fd);
	}
	return ;
}

//NOTE: protect duplicate
void	ft_redirection_function(t_redir *redirs)
{
	int		fd;

	while (redirs)
	{
		if (redirs->type == TOKEN_REDIR_IN || redirs->type == TOKEN_REDIR_OUT
			|| redirs->type == TOKEN_APPEND)
			ft_redir_no_heredoc(redirs->type);
		else if (redirs->type == TOKEN_HEREDOC)
		{
			dup2(redirs->fd, STDIN_FILENO);
			close(redirs->fd);
		}
		redirs = redirs->next_redir;
	}
	return ;
}
