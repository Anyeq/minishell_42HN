/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_main_loop.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asando <asando@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 11:39:22 by asando            #+#    #+#             */
/*   Updated: 2026/03/13 16:22:58 by asando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_token	*ft_create_tokens(t_token **tokens)
{
	char	*line;

	line = readline("minishell$ ");
	if (line == NULL)
	{
		printf("exit\n");
		return (-1);
	}
	if (*line == '\0')
	{
		free(line);
		return (0);
	}
	add_history(line);
	*tokens = ft_lexer_loop(line);
	if (*tokens == NULL)
	{
		free(line);
		return (0);
	}
	free(line);
	return (42);
}

static int	ft_prepare_tokens(t_token **tokens, t_helper *helper)
{
	int	status;

	status = ft_create_tokens(tokens);
	if (status != 42)
		return (status);
	if (ft_expand_tokens(*tokens, helper->envp) == -1)
	{
		ft_free_token_list(tokens);
		return (0);
	}
	return (42);
}

static int	ft_prepare_cmd(t_tokens **tokens, t_cmd **pipeline)
{
	*pipeline = ft_parse(*tokens);
	if (pipeline == NULL)
	{
		ft_free_token_list(tokens);
		return (-1);
	}
	ft_free_token_list(tokens);
	if (ft_prepare_heredoc(*pipeline) == -1)
	{
		ft_free_pipeline(pipeline);
		return (-1);
	}
	return (0);
}

void	minishell_loop(t_helper *helper)
{
	t_token	*tokens;
	t_cmd	*pipeline;
	int		status;

	while (1)
	{
		status = ft_prepare_tokens(&tokens, helper);
		if (status == 0)
			continue ;
		else if (status == -1)
			break ;
		if (ft_prepare_cmd(&tokens, &pipeline))
			continue ;
		ft_executor(&pipeline, helper);
		ft_free_pipeline(&pipeline);
	}
	return ;
}
