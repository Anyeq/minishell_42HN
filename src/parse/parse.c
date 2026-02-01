/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asando <asando@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 19:54:38 by asando            #+#    #+#             */
/*   Updated: 2026/02/01 15:20:36 by asando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

static int	ft_syntax_error(t_token *tokens)
{
	if (tokens == NULL || tokens->type == TOKEN_PIPE)
		return (-1);
	tokens = tokens->next_token;
	while (tokens)
	{
		if (tokens->type == TOKEN_PIPE && tokens->next_token == NULL)
			return (-1);
		if (tokens->type == TOKEN_PIPE && tokens->next_token->type == TOKEN_PIPE)
			return (-1);
		if (tokens->type == TOKEN_REDIR_IN
			|| tokens->type == TOKEN_REDIR_OUT
			|| tokens->type == TOKEN_APPEND
			|| tokens->type == TOKEN_HEREDOC)
		{
			if (tokens->next_token == NULL || tokens->next_token->type
				!= TOKEN_WORD)
				return (-1);
		}
		tokens = tokens->next_token;
	}
	return (0);
}

static int	ft_redir_to_cmd(t_cmd **curr_cmd, t_cmd **pipeline,
			t_token **tokens)
{
	if (ft_add_redir(*curr_cmd, (*tokens)->type, (*tokens)->next_token->value)
		== -1)
	{
		printf("minishell: malloc error");
		ft_free_pipeline(pipeline);
		return (-1);
	}
	*tokens = (*tokens)->next_token;
	return (0);
}

static int	ft_token_to_cmd(t_cmd **curr_cmd, t_cmd **pipeline,
			t_token **tokens)
{
	if ((*tokens)->type == TOKEN_WORD)
	{
		if (ft_add_arg(*curr_cmd, (*tokens)->value) == -1)
		{
			printf("minishell: malloc error");
			ft_free_pipeline(pipeline);
			return (-1);
		}
	}
	else if ((*tokens)->type == TOKEN_REDIR_IN
		|| (*tokens)->type == TOKEN_REDIR_OUT
		|| (*tokens)->type == TOKEN_APPEND
		|| (*tokens)->type == TOKEN_HEREDOC)
	{
		if (ft_redir_to_cmd(curr_cmd, pipeline, tokens) == -1)
			return (-1);
	}
	else if ((*tokens)->type == TOKEN_PIPE)
	{
		ft_add_cmd(pipeline, *curr_cmd);
		*curr_cmd = NULL;
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
	//NOTE: Need to print SYNTAX ERROR here
	if (ft_syntax_error(tokens) == -1)
		return (NULL);
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
