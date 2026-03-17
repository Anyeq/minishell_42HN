/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_redirection.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asando <asando@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 19:19:36 by asando            #+#    #+#             */
/*   Updated: 2026/03/17 19:17:36 by asando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

static void	ft_open_failed(char *filename, int fd)
{
	if (fd == -1)
	{
		perror(filename);
		exit(1);
	}
	return ;
}

static void	ft_redir_no_heredoc(t_redir *redirs)
{
	int	fd;

	if (redirs->type == TOKEN_REDIR_IN)
	{
		fd = open(redirs->filename, O_RDONLY);
		ft_open_failed(redirs->filename, fd);
		dup2(fd, STDIN_FILENO);
		close(fd);
	}
	else if (redirs->type == TOKEN_REDIR_OUT)
	{
		fd = open(redirs->filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		ft_open_failed(redirs->filename, fd);
		dup2(fd, STDOUT_FILENO);
		close(fd);
	}
	else if (redirs->type == TOKEN_APPEND)
	{
		fd = open(redirs->filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
		ft_open_failed(redirs->filename, fd);
		dup2(fd, STDOUT_FILENO);
		close(fd);
	}
	return ;
}

void	ft_redirection_function(t_redir *redirs)
{
	while (redirs)
	{
		if (redirs->type == TOKEN_REDIR_IN || redirs->type == TOKEN_REDIR_OUT
			|| redirs->type == TOKEN_APPEND)
			ft_redir_no_heredoc(redirs);
		else if (redirs->type == TOKEN_HEREDOC)
		{
			dup2(redirs->fd, STDIN_FILENO);
			close(redirs->fd);
		}
		redirs = redirs->next_redir;
	}
	return ;
}
