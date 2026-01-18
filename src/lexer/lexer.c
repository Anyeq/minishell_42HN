/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asando <asando@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 20:30:04 by asando            #+#    #+#             */
/*   Updated: 2026/01/18 13:05:13 by asando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

//NOTE: check again if allocation fail should we return NULL or exit?
//NOTE: value should be dynamically alocated probaby
t_token	*ft_new_token(t_token_type type, char *value, t_flag_quote quote)
{
	t_token	*new_token;

	new_token = malloc(sizeof(t_token));
	if (new_token == NULL)
		return (NULL);
	new_token->type = type;
	new_token->value = value;
	new_token->flag_quote = quote;
	new_token->next_token = NULL;
	return (new_token);
}

//NOTE: what should we do if new_token is NULL
void	ft_add_token(t_token **token_list, t_token *new_token)
{
	t_token	*tmp;

	if (*token_list == NULL)
	{
		*token_list = new_token;
		return ;
	}
	tmp = *token_list;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new_toke;
	return ;
}

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

t_token	*lexer(char *input)
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
		if (ft_is_operator(input[i]))
		{
			i = ft_read_operator(input, i, &token_list);
			continue ;
		}
	}
	return (token_list);
}
