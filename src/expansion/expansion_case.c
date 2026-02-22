/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_case.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asando <asando@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/22 11:09:17 by asando            #+#    #+#             */
/*   Updated: 2026/02/22 11:41:11 by asando           ###   ########.fr       */
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

char	*ft_normal_case(char chr, char **str_to_join)
{
	char	*result;
	char	*buff;

	result = NULL;
	buff = malloc(sizeof(char) * 2);
	if (buff == NULL)
	{
		perror("malloc error");
		return (NULL);
	}
	buff[0] = chr;
	buff[1] = '\0';
	result = ft_join_and_free(*str_to_join, buff);
	*str_to_join = NULL;
	buff = NULL;
	return (result);
}
