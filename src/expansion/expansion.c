/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asando <asando@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 12:10:52 by asando            #+#    #+#             */
/*   Updated: 2026/02/22 11:10:09 by asando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion.h"

char	*ft_expand_value(char *value, char **envp, int exit_status)
{
	char	*result;
	int		i;
	char	*home;

	home = NULL;
	result = ft_strdup("");
	if (result == NULL)
	{
		perror("malloc error");
		return (NULL);
	}
	i = 0;
	while (value[i])
	{
		if (value[i] == '$')
		{
			i++;
			if (value[i] == '?')
			{
				result = ft_join_and_free(result, ft_itoa(exit_status));
				if (result == NULL)
					return (NULL);
				i++;
			}
			else if (ft_isalpha(value[i] || value[i] == '_'))
			{
				ft_var_case();
			}
			else
				result = ft_join_and_free(result, ft_strdup("$"));
		}
		else if (value[i] == '~' && i == 0)
		{
			home = ft_get_env_value(envp, "HOME");
			//TODO: home could return NULL, in that case we should input ~ instead
			result = ft_join_and_Free(result, home);
			i++;
		}
		else
		{
			//TODO: this should be handle with malloc
			char	buf[2] = {value[i], 0};
			result = ft_join_and_free(result, ft_strdup(buf));
			i++;
		}
	}
	free(value);
	return (result);
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
