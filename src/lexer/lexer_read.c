/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_read.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asando <asando@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/18 12:46:20 by asando            #+#    #+#             */
/*   Updated: 2026/01/18 13:03:10 by asando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int	ft_read_operator(char *input, int i, t_token **token_list)
{
	if (input[i] == '>' && input[i + 1] == '>')
	{
		ft_add_token(token_list, ft_new_token(TOKEN_APPEND, NULL, Q_NONE));
		return (i + 2);
	}
	else if (input[i] == '<' && input[i + 1] == '<')
	{
		ft_add_token(token_list, ft_new_token(TOKEN_HEREDOC, NULL, Q_NONE));
		return (i + 2);
	}
	else if (input[i] == '>')
		ft_add_token(token_list, ft_new_token(TOKEN_REDIR_IN, NULL, Q_NONE));
	else if (input[i] == '<')
		ft_add_token(token_list, ft_new_token(TOKEN_REDIR_OUT, NULL, Q_NONE));
	else if (input[i] == '|')
		ft_add_token(token_list, ft_new_token(TOKEN_PIPE, NULL, Q_NONE));
	return (i + 1);
}

int	ft_read_quote(char *input, int i, t_token **token_list)
{
	t_flag_quote	quote;
	int				start;
	char			*value;

	value = NULL;
	start = i + 1;
	if (input[i] == '\'')
		quote = Q_SINGLE;
	else if (input[i] == '"')
		quote = Q_DOUBLE;
	while (input[i] && input[i] != '\'' && input[i] != '"')
		i++;
	if (input[i] == '\0')
	{
		//NOTE: must handle Error!
		return (-1);
	}
	value = ft_substr(input, start, i - start);
	ft_add_token(token_list, ft_new_token(TOKEN_WORD, value, quote));
	return (i + 1);
}
