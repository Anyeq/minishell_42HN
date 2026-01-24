/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asando <asando@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/18 14:29:43 by asando            #+#    #+#             */
/*   Updated: 2026/01/24 12:09:30 by asando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int	ft_is_whitespace(char c)
{
	if (c == ' ' || c == '\t' || c == '\n')
		return (42);
	return (0);
}

int	ft_is_operator(char c)
{
	if (c == '>' || c == '|' || c == '<')
		return (42);
	return (0);
}

int	ft_is_quote(char c)
{
	if (c == '\'' || c == '"')
		return (42);
	return (0);
}

void	ft_lexer_error(t_flag_error f_error)
{
	if (f_error & ERR_MALLOC)
		printf("minishell: failed malloc\n");
	else if (f_error & ERR_SYNTAX_UNCLOSED)
		printf("minishell: syntax error: unclosed quote\n");
	return ;
}

void	ft_malloc_error(t_token **token_list)
{
	ft_free_token_list(token_list);
	ft_lexer_error(ERR_MALLOC);
	return ;
}
