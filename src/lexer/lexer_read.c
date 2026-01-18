/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_read.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asando <asando@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/18 12:46:20 by asando            #+#    #+#             */
/*   Updated: 2026/01/18 14:34:02 by asando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

//NOTE: For operator the value will be null but need to check this again later
//NOTE: Edge case need to be check in this case for example when after 
//operator there another stuff
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

//NOTE: how to efficiently add libft also on lexer.h or only in minishell.h
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
	while (input[i] && !ft_is_quote(input[i]))
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

int	ft_read_word(char *input, int i, t_token **token_list)
{
	int		start;
	char	*value;

	value = NULL;
	start = i;
	while (!ft_is_whitespace(input[i]) && !ft_is_operator(input[i])
		&& !ft_is_quote(input[i]))
			i++;
	value = ft_substr(input, start, i - start);
	ft_add_token(token_list, ft_new_token(TOKEN_WORD, value, Q_NONE));
	return (i);
}
