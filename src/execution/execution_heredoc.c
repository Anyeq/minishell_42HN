/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_heredoc.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asando <asando@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 13:55:38 by asando            #+#    #+#             */
/*   Updated: 2026/03/16 23:11:15 by asando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

static void	ft_write_line(int fd, const char *line)
{
	ssize_t	line_size;

	line_size = ft_strlen(line);
	if (write(fd, line, line_size) < line_size)
	{
		perror("write error");
		return ;
	}
	if (write(fd, "\n", 1) < 1)
		perror("write error");
	return ;
}

static int	ft_read_heredoc(const char *delimiter, int write_fd)
{
	char	*line;
	size_t	delimiter_size;

	delimiter_size = ft_strlen(delimiter);
	while (1)
	{
		line = readline("> ");
		if (line == NULL)
			break ;
		if (ft_strncmp(line, delimiter, delimiter_size) == 0)
		{
			free(line);
			break ;
		}
		ft_write_line(write_fd, line);
		free(line);
	}
	return (0);
}

static int	ft_heredoc(t_redir *redirs)
{
	int	pipe_fd[2];

	if (pipe(pipe_fd) == -1)
	{
		perror("pipe error");
		return (-1);
	}
	if (ft_read_heredoc(redirs->filename, pipe_fd[1]) == -1)
	{
		close(pipe_fd[0]);
		close(pipe_fd[1]);
		return (-1);
	}
	close(pipe_fd[1]);
	redirs->fd = pipe_fd[0];
	return (0);
}

static int	ft_cmd_heredoc(t_cmd *cmd)
{
	t_redir	*redir;

	redir = cmd->redirs;
	while (redir)
	{
		if (redir->type == TOKEN_HEREDOC)
		{
			if (ft_heredoc(redir) == -1)
				return (-1);
		}
		redir = redir->next_redir;
	}
	return (0);
}

int	ft_prepare_heredoc(t_cmd *pipeline)
{
	t_cmd	*curr;

	curr = pipeline;
	while (curr)
	{
		if (ft_cmd_heredoc(curr) == -1)
			return (-1);
		curr = curr->next_cmd;
	}
	return (0);
}
