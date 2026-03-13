/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asando <asando@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 19:11:21 by asando            #+#    #+#             */
/*   Updated: 2026/03/13 11:58:45 by asando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H
# include "lexer.h"
# include "parse.h"
# include "libft.h"
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <sys/wait.h>

typedef struct s_helper
{
	int		n_cmd;
	char	**envp;
}	t_helper;
// Execution utils (execution_process_utils.c)
int		ft_cmd_count(t_cmd *cmd);
void	ft_clean_pipe_allocation(int n, int **address);
void	ft_close_pipes(int n, int **pipes);

// Pipe Creation function (execution_pipe.c)
int		**ft_init_pipe(int n_cmd);

// Rediraction purpose function (execution_redirection.c)
void	ft_redirection_function(t_redir *redirs);

// Heredoc purposed function (execution_heredoc.c)
int		ft_prepare_heredoc(t_cmd *pipeline);

// Parent process function (execution_parent_process.c)
int		ft_parent_process(int **pipes, pid_t *pids, int	n_cmd);

// Child process function (execution_child_process.c)
void	ft_run_child_process(t_cmd *cmd, int n_cmd, int *pids, int **pipes);

// Main function in execution (execution_executor.c)
void	ft_executor(t_cmd *pipeline);
#endif
