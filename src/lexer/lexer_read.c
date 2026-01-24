/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_read.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asando <asando@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/18 12:46:20 by asando            #+#    #+#             */
/*   Updated: 2026/01/24 11:58:40 by asando           ###   ########.fr       */
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
	return (TOKEN_NONE);
}

//NOTE: For operator the value will be null but need to check this again later
//NOTE: Edge case need to be check in this case for example when after 
//operator there another stuff
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

//NOTE: check if value and new token should be nulled at the beginning
int	ft_read_quote(char *input, int i, t_token **token_list)
{
	t_flag_quote	quote;
	int				start;
	char			*value;
	t_token			*new_token;

	start = i + 1;
	if (input[i] == '\'')
		quote = Q_SINGLE;
	else if (input[i] == '"')
		quote = Q_DOUBLE;
	i++;
	while (input[i] && !ft_is_quote(input[i]))
		i++;
	if (input[i] == '\0')
		return (-1);
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

int	ft_read_word(char *input, int i, t_token **token_list)
{
	int		start;
	char	*value;
	t_token	*new_token;

	new_token = NULL;
	value = NULL;
	start = i;
	while (!ft_is_whitespace(input[i]) && !ft_is_operator(input[i])
		&& !ft_is_quote(input[i]) && input[i])
		i++;
	value = ft_substr(input, start, i - start);
	new_token = ft_new_token(TOKEN_WORD, value, Q_NONE);
	if (new_token == NULL || value == NULL)
	{
		ft_malloc_error(token_list);
		return (-1);
	}
	ft_add_token(token_list, new_token);
	return (i);
}
