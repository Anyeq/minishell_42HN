/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asando <asando@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 12:10:52 by asando            #+#    #+#             */
/*   Updated: 2026/02/13 12:19:18 by asando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion.h"

void	ft_expand_tokens(t_token *tokens, char **envp, int exit_status)
{
	while (tokens)
	{
		if (tokens->type == TOKEN_WORD && tokens->flag_quote == Q_DOUBLE)
			tokens->value = ft_expand_value(tokens->value, envp, exit_status);
		tokens = tokens->next_token;
	}
	return ;
}
