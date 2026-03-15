/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asando <asando@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/13 17:28:50 by asando            #+#    #+#             */
/*   Updated: 2026/03/15 11:42:08 by asando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

static int	ft_split_key_value(const char *line, char **key, char **value)
{
	int	i;

	i = 0;
	while (line[i] && line[i] != '=')
		i++;
	*key = ft_substr(line, 0, i);
	if (*key == NULL)
	{
		perror("minishell: malloc error");
		return (-1);
	}
	if (line[i] == '=')
	{
		*value = ft_strdup(line + i + 1);
		free(*key);
		if (*value == NULL)
		{
			perror("minishell: malloc error");
			return (-1);
		}
	}
	else
		*value = NULL;
	return (0);
}

static t_env	*ft_prepare_new_env(char *envp, t_env *env_list,
					char **key, char **value)
{
	t_env	*new_env;

	new_env = NULL;
	if (ft_split_key_value(envp, key, value))
	{
		ft_clean_struct_env(env_list, key, value);
		return (NULL);
	}
	new_env = ft_env_new(*key, *value);
	if (new_env == NULL)
	{
		ft_clean_struct_env(env_list, key, value);
		return (NULL);
	}
	return (new_env);
}

t_env	*ft_init_env(char **envp)
{
	t_env	*env_list;
	t_env	*new_env;
	char	*key;
	char	*value;
	int		i;

	env_list = NULL;
	new_env = NULL;
	i = 0;
	while (envp[i])
	{
		new_env = ft_prepare_new_env(envp[i], env_list, &key, &value);
		if (new_env == NULL)
			return (NULL);
		ft_add_env(&env_list, new_env);
		free(key);
		free(value);
		i++;
	}
	return (env_list);
}
