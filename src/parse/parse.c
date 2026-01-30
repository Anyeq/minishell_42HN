/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asando <asando@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 19:54:38 by asando            #+#    #+#             */
/*   Updated: 2026/01/30 21:43:51 by asando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static int	ft_redir_to_cmd(t_cmd **curr_cmd, t_cmd **pipeline, t_token **tokens)
{
	if (*tokens->next_token == NULL || *tokens->next_token->type != TOKEN_WORD)
	{
		printf("minishell: syntax error");
		ft_free_pipeline(pipeline);
		return (-1);
	}
	if (ft_add_redir(*curr_cmd, *tokens->type, *tokens->next_token->value) == -1)
	{
		printf("minishell: malloc error");
		ft_free_pipeline(pipeline);
		return (-1);
	}
	*tokens = *tokens->next_token;
	return (0);
}

static int	ft_token_to_cmd(t_cmd **curr_cmd, t_cmd **pipeline, t_token **tokens)
{
	if (*tokens->type == TOKEN_WORD)
	{
		if (ft_add_arg(*curr_cmd, *tokens->value) == -1)
		{
			printf("minishell: malloc error");
			ft_free_pipeline(pipeline);
			return (-1);
		}
	}
	else if (*token->type == TOKEN_REDIR_IN 
		|| *tokens->type == TOKEN_REDIR_OUT 
		|| *tokens->type == TOKEN_APPEND 
		|| *tokens->type == TOKEN_HEREDOC)
	{
		if (ft_redir_to_cmd(curr_cmd, pipeline, tokens) == -1)
			return (-1);
	}
	else if (*tokens->type == TOKEN_PIPE)
	{
		ft_add_cmd(pipeline, *curr_cmd);
		*curr_cmd == NULL;
	}
	return (0);
}

//BUG: When it return NULL than we have to handle memorry allocation for token
t_cmd	*parse_loop(t_token *tokens)
{
	t_cmd	*pipeline;
	t_cmd	*curr_cmd;

	curr_cmd = NULL;
	pipeline = NULL;
	while (tokens)
	{
		if (curr_cmd == NULL)
			curr_cmd = ft_new_cmd();
		if (curr_cmd == NULL)
		{
			printf("minishell: malloc error");
			ft_free_pipeline(&pipeline);
			return (NULL);
		}
		if (ft_token_to_cmd(&curr_cmd, &pipeline, &tokens) == -1)
			return (NULL);
		tokens = tokens->next_token;
	}
	if (curr_cmd)
		ft_add_cmd(&pipeline, curr_cmd);
	return (pipeline);
}
