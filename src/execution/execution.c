/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asando <asando@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 13:55:38 by asando            #+#    #+#             */
/*   Updated: 2026/02/05 19:10:52 by asando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	ft_write_line(int fd, const char *line)
{
	size_t	line_size;

	line_size = ft_strlen(line);
	write(fd, line, line_size);
	write(fd, "\n", 1);
	return ;
}

int	ft_read_heredoc(const char *delimiter, int write_fd)
{
	char	*line;
	size_t	delimiter_size;

	delimiter_size = ft_strlen(delimiter);
	while (1)
	{
		line = readline("> ");
		//RETURN NULL WHEN READLINE READ EOF
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

int	ft_single_heredoc(t_redir *redirs)
{
	int	pipe_fd[2];

	if (pipe(pipe_fd) == -1)
		return (-1);
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

int	ft_cmd_heredoc(t_cmd *cmd)
{
	t_redir	*redir;

	redir = cmd->redirs;

	while (redir)
	{
		if (redir->type == TOKEN_HEREDOC)
		{
			if (ft_single_heredoc(redir) == -1)
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

void	ft_redirection_function(t_redir *redirs)
{
	int		fd;

	while (redirs)
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
		else if (redirs->type == TOKEN_HEREDOC)
		{
			dup2(redirs->fd, STDIN_FILENO);
			close(redirs->fd);
		}
		redirs = redirs->next_redir;
	}
	return ;
}
