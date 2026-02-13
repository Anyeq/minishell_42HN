/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asando <asando@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 12:10:52 by asando            #+#    #+#             */
/*   Updated: 2026/02/13 15:58:10 by asando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion.h"

char	*ft_join_and_free(char *str1, char *str2)
{
	char	*res;

	res = ft_strjoin(str1, str2);
	if (res == NULL)
	{
		perror("malloc error");
		free(str1);
		free(str2);
		return (res);
	}
	free(str1);
	free(str2);
	return (res);
}

char	*ft_expand_value(char *value, char **envp, int exit_status)
{
	char	*result;
	int		i;

	result = ft_strdup("");
	if (result == NULL)
		return (NULL);
	i = 0;
	while (value[i])
	{
		if (value[i] == '$')
		{
			i++;
			if (value[i] == '?')
			{
				result = ft_join_and_free(result, ft_itoa(exit_status));
				i++;
			}
		}
	}
}

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
