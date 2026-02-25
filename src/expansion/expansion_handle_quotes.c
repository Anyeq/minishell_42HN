/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_handle_quotes.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asando <asando@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/22 11:06:14 by asando            #+#    #+#             */
/*   Updated: 2026/02/25 15:38:08 by asando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion.h"

static char	*ft_strip_quote(char *str)
{
	char	*result;
	int		i;
	int		j;
	char	c;

	i = 0;
	j = 0;
	result = malloc(ft_strlen(str) + 1);
	//TODO: check the logic again in the way it copies the char
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '"')
		{
			c = str[i++];
			while (str[i] && str[i] != c)
				result[j++] = str[i++];
			if (str[i] == c)
				i++;
		}
		else
			result[j++] = str[i++];
	}
	result[j] = 0;
	//TODO: check if str have to be cleaned
	free(str);
	return (result);
}

void	ft_remove_quotes(t_token *tokens)
{
	while (tokens)
	{
		if (tokens->type == TOKEN_WORD)
			tokens->value = ft_strip_quotes(tokens->value);
		tokens->next_token;
	}
}
