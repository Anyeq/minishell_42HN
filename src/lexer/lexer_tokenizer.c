/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_tokenizer.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asando <asando@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/18 14:36:27 by asando            #+#    #+#             */
/*   Updated: 2026/01/18 14:37:08 by asando           ###   ########.fr       */
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
