/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asando <asando@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 19:54:38 by asando            #+#    #+#             */
/*   Updated: 2026/03/20 07:32:50 by asando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

static int	ft_if_redir_operator(t_token *token)
{
	if (token->type == TOKEN_REDIR_IN
		|| token->type == TOKEN_REDIR_OUT
		|| token->type == TOKEN_APPEND
		|| token->type == TOKEN_HEREDOC)
		return (0);
	return (-1);
}

static int	ft_syntax_error(t_token *tokens)
{
	int	res;

	res = 0;
	if (tokens == NULL || tokens->type == TOKEN_PIPE)
		res = -1;
	while (tokens && res == 0)
	{
		if (tokens->type == TOKEN_PIPE && tokens->next_token == NULL)
			res = -1;
		else if (tokens->type == TOKEN_PIPE
			&& tokens->next_token->type == TOKEN_PIPE)
			res = -1;
		else if (ft_if_redir_operator(tokens) == 0)
		{
			if (tokens->next_token == NULL || tokens->next_token->type
				!= TOKEN_WORD)
				res = -1;
		}
		tokens = tokens->next_token;
		if (res == -1)
			printf("minishell: syntax error");
	}
	return (res);
}

static int	ft_redir_to_cmd(t_cmd **curr_cmd, t_cmd **pipeline,
			t_token **tokens)
{
	if (ft_add_redir(*curr_cmd, (*tokens)->type, (*tokens)->next_token->value)
		== -1)
	{
		ft_parse_error(pipeline);
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
			ft_parse_error(pipeline);
			return (-1);
		}
	}
	else if (ft_if_redir_operator(*tokens) == 0)
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

t_cmd	*ft_parse_loop(t_token *tokens)
{
	t_cmd	*pipeline;
	t_cmd	*curr_cmd;

	curr_cmd = NULL;
	pipeline = NULL;
	if (ft_syntax_error(tokens) == -1)
		return (NULL);
	while (tokens)
	{
		if (curr_cmd == NULL)
			curr_cmd = ft_new_cmd();
		if (curr_cmd == NULL)
		{
			ft_parse_error(&pipeline);
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
