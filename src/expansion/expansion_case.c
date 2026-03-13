/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_case.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asando <asando@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/22 11:09:17 by asando            #+#    #+#             */
/*   Updated: 2026/03/13 09:42:50 by asando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion.h"

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

char	*ft_var_case(char **result, char *str, int *i, char **envp)
{
	char	*key;
	char	*val;
	char	*return_str;
	int		start;

	start = *i;
	return_str = NULL;
	while (ft_isalnum(str[*i]) || str[*i] == '_')
		*i = *i + 1;
	key = ft_substr(str, start, *i - start);
	val = ft_get_env_value(envp, key);
	if (val)
		return_str = ft_join_and_free(*result, ft_strdup(val));
	else if (val == NULL)
		return_str = ft_join_and_free(*result, ft_strdup(""));
	*result = NULL;
	free(key);
	return (return_str);
}

char	*ft_exit_status_case(char **result, int *i)
{
	char	*return_val;
	char	*str_exit_status;

	str_exit_status = ft_itoa(g_exit_status);
	if (str_exit_status == NULL)
	{
		perror("minishell: malloc error");
		return (NULL);
	}
	return_val = ft_join_and_free(*result, str_exit_status);
	if (return_val == NULL)
		return (NULL);
	*result = NULL;
	str_exit_status = NULL;
	*i = *i + 1;
	return (return_val);
}

char	*ft_normal_case(char chr, char **result, int *i)
{
	char	*return_val;
	char	*buff;

	return_val = NULL;
	buff = malloc(sizeof(char) * 2);
	if (buff == NULL)
	{
		perror("malloc error");
		return (NULL);
	}
	buff[0] = chr;
	buff[1] = '\0';
	return_val = ft_join_and_free(*result, buff);
	*result = NULL;
	buff = NULL;
	*i = *i + 1;
	return (return_val);
}

char	*ft_home_case(char **result, char **envp, int *i)
{
	char	*home;
	char	*return_val;

	home = ft_get_env_value(envp, "HOME");
	if (home == NULL)
		return_val = ft_join_and_free(*result, ft_strdup("~"));
	else
		return_val = ft_join_and_free(*result, home);
	home = NULL;
	*result = NULL;
	*i = *i + 1;
	return (return_val);
}
