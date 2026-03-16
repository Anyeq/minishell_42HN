/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asando <asando@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 20:30:04 by asando            #+#    #+#             */
/*   Updated: 2026/03/16 22:19:34 by asando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

static int	ft_lexer_read(char *input, int i, t_token **token_list)
{
	if (ft_is_operator(input[i]))
	{
		i = ft_read_operator(input, i, token_list);
		return (i);
	}
	if (ft_is_quote(input[i]))
	{
		i = ft_read_quote(input, i, token_list);
		if (i == -1)
		{
			ft_lexer_error(ERR_SYNTAX_UNCLOSED);
			ft_free_token_list(token_list);
			return (i);
		}
		if (i == -2)
			return (i);
		return (i);
	}
	i = ft_read_word(input, i, token_list);
	return (i);
}

t_token	*lexer_loop(char *input)
{
	t_token	*token_list;
	int		i;

	i = 0;
	token_list = NULL;
	while (input[i])
	{
		while (ft_is_whitespace(input[i]))
			i++;
		if (input[i] == '\0')
			break ;
		i = ft_lexer_read(input, i, &token_list);
		if (i < 0)
			return (NULL);
	}
	return (token_list);
}
