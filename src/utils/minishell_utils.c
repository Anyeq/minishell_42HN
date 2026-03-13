/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asando <asando@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 08:22:59 by asando            #+#    #+#             */
/*   Updated: 2026/03/13 21:17:58 by asando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_env_size(t_env *env)
{
	int	count;

	count = 0;
	while (env)
	{
		count++;
		env = env->next;
	}
	return (count);
}

char	**ft_create_envp(t_env *env)
{
	int		size;
	char	**envp;
	int		i;

	size = ft_env_size(env);
	envp = malloc(sizeof(char *) * (size + 1));
	i = 0;
	if (envp == NULL)
	{
		perror("minishell: malloc error");
		return (NULL);
	}
	while (env)
	{
		if (env->value)
		{
			envp[i] = ft_strjoin3(env->key, "=", env->value);
			if (envp[i] == NULL)
			{
				//BUG: Cleaning allocation
			}
		}
		else
		{
			envp[i] = ft_strdup(env->key);
			if (envp[i] == NULL)
			{
				//BUG: Cleaning allocation
			}
		}
		env = env->next;
		i++;
	}
	envp[i] = NULL;
	return (envp);
}

char	**ft_copy_envp(char **envp)
{
	char	**result;
	int		n_envp;
	int		i;

	n_envp = 0;
	i = 0;
	while (envp[n_envp])
		n_envp++;
	result = malloc(sizeof(char *) * (n_envp + 1));
	if (result == NULL)
		return (result);
	while (i < n_envp)
	{
		result[i] = ft_strdup(envp[i]);
		if (result[i] == NULL)
		{
			while (i-- > -1)
				free(result[i]);
			free(result);
			return (NULL);
		}
		i++;
	}
	result[n_envp] = NULL;
	return (result);
}
