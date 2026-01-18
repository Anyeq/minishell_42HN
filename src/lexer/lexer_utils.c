/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asando <asando@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/18 14:29:43 by asando            #+#    #+#             */
/*   Updated: 2026/01/18 15:11:08 by asando           ###   ########.fr       */
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

void	ft_lexer_error(void)
{
	printf("minishell: syntax error: unclosed quote");
	return ;
}
