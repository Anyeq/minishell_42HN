/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asando <asando@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 20:30:04 by asando            #+#    #+#             */
/*   Updated: 2026/01/18 14:37:55 by asando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

t_token	*lexer(char *input)
{
	t_token	*token_list;
	int		i;
	int		n_content;

	i = 0;
	token_list = NULL;
	n_content = 0;
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
		if (ft_is_quote(input[i]))
		{
			n_content = ft_read_quote(input, i, &token_list);
			if (n_content == -1)
			{
				//NOTE: Handle Error here
				return (NULL)
			}
			i = n_content;
			continue ;
		}
		i = ft_read_word(input, i, &token_list);
	}
	return (token_list);
}
