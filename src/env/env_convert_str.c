/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asando <asando@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 08:22:59 by asando            #+#    #+#             */
/*   Updated: 2026/03/15 11:37:05 by asando           ###   ########.fr       */
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

static	void	ft_clean_env_allocation(char ***envp, int i)
{
	while (--i >= 0)
		free((*envp)[i]);
	free(*envp);
	return ;
}

static int	ft_arrange_str(char ***envp, t_env *env, int i)
{
	if (env->value)
	{
		(*envp)[i] = ft_strjoin3(env->key, "=", env->value);
		if ((*envp)[i] == NULL)
		{
			ft_clean_allocation(envp, i);
			perror("minishell: malloc error");
			return (-1);
		}
	}
	else
	{
		(*envp)[i] = ft_strdup(env->key);
		if ((*envp)[i] == NULL)
		{
			ft_clean_allocation(envp, i);
			perror("minishell: malloc error");
			return (-1);
		}
	}
	return (0);
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
		if (ft_arrange_str(&envp, env, i) == -1)
			return (NULL);
		env = env->next;
		i++;
	}
	envp[i] = NULL;
	return (envp);
}
