/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_case.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asando <asando@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/22 11:09:17 by asando            #+#    #+#             */
/*   Updated: 2026/03/21 18:55:09 by asando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion.h"

char	*ft_number_case(char **result, char *str, int *i)
{
	char	*return_str;

	if (str[*i] == '0')
	{
		return_str = ft_join_and_free(*result, ft_strdup("-minishell"));
		*result = NULL;
	}
	else
	{
		return_str = ft_join_and_free(*result, ft_strdup(""));
		*result = NULL;
	}
	*i = *i + 1;
	return (return_str);
}

char	*ft_var_case(char **result, char *str, int *i, t_shell *shell)
{
	char	*key;
	char	*val;
	char	*return_str;
	int		start;
	char	*env_var;

	start = *i;
	return_str = NULL;
	while (ft_isalnum(str[*i]) || str[*i] == '_')
		*i = *i + 1;
	key = ft_substr(str, start, *i - start);
	env_var = get_env_value(shell->env, key);
	if (env_var == NULL)
		val = NULL;
	else
		val = ft_strdup(env_var);
	if (val)
		return_str = ft_join_and_free(*result, ft_strdup(val));
	else if (val == NULL)
		return_str = ft_join_and_free(*result, ft_strdup(""));
	*result = NULL;
	free(key);
	return (return_str);
}

char	*ft_exit_status_case(char **result, int *i, t_shell *shell)
{
	char	*return_val;
	char	*str_exit_status;

	str_exit_status = ft_itoa(shell->exit_status);
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
		perror("minishell: malloc error");
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

char	*ft_home_case(char **result, t_shell *shell, int *i)
{
	char	*home;
	char	*return_val;

	home = ft_strdup(get_env_value(shell->env, "HOME"));
	if (home == NULL)
		return_val = ft_join_and_free(*result, ft_strdup("~"));
	else
		return_val = ft_join_and_free(*result, home);
	home = NULL;
	*result = NULL;
	*i = *i + 1;
	return (return_val);
}
