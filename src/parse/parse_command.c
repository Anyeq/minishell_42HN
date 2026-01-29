/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asando <asando@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 19:54:38 by asando            #+#    #+#             */
/*   Updated: 2026/01/29 19:55:27 by asando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

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
		//NOTE: When its NULL we have to handle the token memorry allocation
		if (curr_cmd == NULL)
			return (NULL);
		if (tokens->type == TOKEN_WORD)
			ft_add_arg(curr_cmd, tokens->value);
		else if (token->type == TOKEN_REDIR_IN 
		|| tokens->type == TOKEN_REDIR_OUT
		|| tokens->type == TOKEN_APPEND
		|| tokens->type != TOKEN_HEREDOC)
		{
			//NOTE: Here we have to also handle memorry allocation
			if (tokens->next_token == NULL || tokens->next_token->type != TOKEN_WORD)
				return (NULL);
			ft_add_redir(curr_cmd, tokens->type, tokens->next_token->value);
			tokens = tokens->next_token;
		}
		else if (tokens->type == TOKEN_PIPE)
		{
			ft_add_cmd(&pipeline, curr_cmd);
			curr_cmd = NULL;
		}
		tokens = tokens->next_token;
	}
	if (curr_cmd)
		ft_add_cmd(&pipeline, curr_cmd);
	return (pipeline);
}
