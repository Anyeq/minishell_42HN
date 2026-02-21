/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asando <asando@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 12:10:52 by asando            #+#    #+#             */
/*   Updated: 2026/02/21 12:19:38 by asando           ###   ########.fr       */
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

char	*ft_get_env_value(char **envp, char *key)
{
	int	len;
	int	i;

	i = 0;
	if (key == NULL)
		return (NULL);
	len = ft_strlen(key);
	while (envp[i])
	{
		if (ft_strncmp(envp[i], key, len) == 0 && envp[i][len] == '=')
			return (envp[i] + len + 1);
		i++;
	}
	return (NULL);
}

char	*ft_var_case(char **result, char *str, int i, char **envp)
{
	char	*key;
	char	*val;
	char	*return_str;
	int		start;

	start = i;
	return_str = NULL;
	while (ft_isalnum(str[i]) || str[i] == '_')
		i++;
	key = ft_substr(str, start, i - start);
	val = ft_get_env_value(envp, key);
	if (val)
		return_str = ft_join_and_free(*result, ft_strdup(val));
	else if (val == NULL)
		return_str = ft_join_and_free(*result, ft_strdup(""));
	*result = NULL;
	free(key);
	return (return_str);
}

char	*ft_exit_status_case(char **result, char *str, int i, char **envp)
{
	char	*return_val;
	char	*str_exit_status;

	str_exit_status = ft_itoa(exit_status);
	if (str_exit_status == NULL)
	{
		perror("malloc error");
		return (NULL);
	}
	return_val = ft_join_and_free(*result, str_exit_status);
	if (return_val == NULL)
		return (NULL);
	*result = NULL;
	return (return_val);
}

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
