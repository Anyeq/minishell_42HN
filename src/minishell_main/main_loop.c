/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asando <asando@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 11:39:22 by asando            #+#    #+#             */
/*   Updated: 2026/03/21 20:49:39 by asando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_create_tokens(t_token **tokens, t_shell *shell)
{
	shell->input = readline("minishell$ ");
	if (shell->input == NULL)
	{
		printf("exit\n");
		return (-1);
	}
	if (*(shell->input) == '\0')
	{
		free(shell->input);
		return (0);
	}
	add_history(shell->input);
	*tokens = ft_lexer_loop(shell->input);
	if (*tokens == NULL)
	{
		free(shell->input);
		return (0);
	}
	free(shell->input);
	shell->input = NULL;
	return (42);
}

static int	ft_prepare_tokens(t_token **tokens, t_shell *shell)
{
	int	status;

	status = ft_create_tokens(tokens, shell);
	if (status != 42)
		return (status);
	if (ft_expand_tokens(*tokens, shell) == -1)
	{
		ft_free_token_list(tokens);
		return (0);
	}
	return (42);
}

static int	ft_prepare_cmd(t_token **tokens, t_cmd **pipeline)
{
	*pipeline = ft_parse_loop(*tokens);
	if (pipeline == NULL)
	{
		ft_free_token_list(tokens);
		return (-1);
	}
	ft_free_token_list(tokens);
	ft_setup_signals_heredoc();
	if (ft_prepare_heredoc(*pipeline) == -1)
	{
		ft_setup_signals_shell();
		ft_free_pipeline(pipeline);
		return (-1);
	}
	ft_setup_signals_shell();
	return (0);
}

void	shell_loop(t_shell *shell)
{
	t_token	*tokens;
	int		status;

	ft_setup_signals_shell();
	while (!shell->should_exit)
	{
		status = ft_prepare_tokens(&tokens, shell);
		if (status == 0)
			continue ;
		else if (status == -1)
			break ;
		if (ft_prepare_cmd(&tokens, &(shell->cmds)))
			continue ;
		ft_executor(shell);
		ft_free_pipeline(&(shell->cmds));
	}
	return ;
}
