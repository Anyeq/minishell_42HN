/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_read.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asando <asando@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/18 12:46:20 by asando            #+#    #+#             */
/*   Updated: 2026/03/19 23:22:18 by asando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

static t_token_type	ft_read_token_type(char *input, int i)
{
	if (input[i] == '>' && input[i + 1] == '>')
		return (TOKEN_APPEND);
	else if (input[i] == '<' && input[i + 1] == '<')
		return (TOKEN_HEREDOC);
	else if (input[i] == '>')
		return (TOKEN_REDIR_IN);
	else if (input[i] == '<')
		return (TOKEN_REDIR_OUT);
	else if (input[i] == '|')
		return (TOKEN_PIPE);
	return (TOKEN_WORD);
}

int	ft_read_operator(char *input, int i, t_token **token_list)
{
	t_token			*new_token;
	t_token_type	token_type;

	new_token = NULL;
	token_type = ft_read_token_type(input, i);
	new_token = ft_new_token(token_type, NULL, Q_NONE);
	if (new_token == NULL)
	{
		ft_malloc_error(token_list);
		return (-1);
	}
	ft_add_token(token_list, new_token);
	if (input[i] == '>' && input[i + 1] == '>')
		return (i + 2);
	else if (input[i] == '<' && input[i + 1] == '<')
		return (i + 2);
	else if (input[i] == '>')
		return (i + 1);
	else if (input[i] == '<')
		return (i + 1);
	else if (input[i] == '|')
		return (i + 1);
	return (-1);
}

static int	ft_read_quote(char *input, t_flag_quote *quote, int i)
{
	char	c_quote;

	c_quote = input[i];
	if (input[i] == '\'' || input[i] == '"')
	{
		c_quote = input[i];
		if (c_quote == '\'')
			*quote = Q_SINGLE;
		else
			*quote = Q_DOUBLE;
		i++;
		while (input[i] && input[i] != c_quote)
			i++;
		if (input[i] == '\0')
			return (-1);
		i++;
	}
	return (i);
}

int	ft_read_word(char *input, int i, t_token **token_list)
{
	int				start;
	char			*value;
	t_token			*new_token;
	t_flag_quote	quote;

	start = i;
	quote = Q_NONE;
	while (input[i] && !ft_is_whitespace(input[i])
		&& !ft_is_operator(input[i]))
	{
		i = ft_read_quote(input, &quote, i);
		if (i < 0)
			return (i);
		else
			i++;
	}
	value = ft_substr(input, start, i - start);
	new_token = ft_new_token(TOKEN_WORD, value, quote);
	if (new_token == NULL || value == NULL)
	{
		ft_malloc_error(token_list);
		return (-2);
	}
	ft_add_token(token_list, new_token);
	return (i + 1);
}
