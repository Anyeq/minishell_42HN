/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asando <asando@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 13:55:38 by asando            #+#    #+#             */
/*   Updated: 2026/02/05 14:48:52 by asando           ###   ########.fr       */
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
