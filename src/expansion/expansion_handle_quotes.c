/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_handle_quotes.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asando <asando@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/22 11:06:14 by asando            #+#    #+#             */
/*   Updated: 2026/03/19 22:33:12 by asando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion.h"

static void	ft_quote_found(char *str, int *i, int *j, char *result)
{
	char	quote;

	quote = str[*i];
	*i = *i + 1;
	while (str[*i] && str[*i] != quote)
		result[(*j)++] = str[(*i)++];
	if (str[*i] == quote)
		(*i)++;
	return ;
}

//NOTE: Memmory allocation allocate with quote (inefficient)
static char	*ft_strip_quotes(char *str)
{
	char	*result;
	int		i;
	int		j;

	i = 0;
	j = 0;
	result = malloc(ft_strlen(str) + 1);
	if (result == NULL)
	{
		perror("minishell: malloc error");
		return (NULL);
	}
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '"')
			ft_quote_found(str, &i, &j, result);
		else
			result[j++] = str[i++];
	}
	result[j] = '\0';
	if (result)
		free(str);
	return (result);
}

//NOTE: skip non quote tokens
int	ft_remove_quotes(t_token *tokens)
{
	while (tokens)
	{
		if (tokens->type == TOKEN_WORD)
		{
			tokens->value = ft_strip_quotes(tokens->value);
			if (tokens->value == NULL)
				return (-1);
		}
		tokens = tokens->next_token;
	}
	return (0);
}
