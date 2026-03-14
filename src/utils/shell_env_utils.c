/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_env_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asando <asando@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/13 17:28:50 by asando            #+#    #+#             */
/*   Updated: 2026/03/14 21:30:38 by asando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

static int	ft_prepare_key_value(t_env **node, const char *key,
								 const char *value)
{
	(*node)->key = ft_strdup(key);
	if ((*node)->key == NULL)
	{
		perror("minishell: malloc error");
		return (-1);
	}
	if (value)
	{
		(*node)->value = ft_strdup(value);
		if ((*node)->value == NULL)
		{
			free((*node)->key);
			free(*node);
			perror("minishell: malloc error");
			return (-1);
		}
	}
	return (0);
}

static t_env	*ft_env_new(const char *key, const char *value)
{
	t_env	*node;

	node = malloc(sizeof(t_env));
	if (ft_prepare_key_value(&node, key, value) == -1)
		return (NULL);
	if (node == NULL)
	{
		perror("minishell: malloc error");
		return (NULL);
	}
	}
	else
		node->value = NULL;
	node->next = NULL;
	return (node);
}

static void	ft_add_env(t_env **env, t_env *new_node)
{
	t_env	*tmp;

	tmp = *env;
	if (*env == NULL)
	{
		*env = new_node;
		return ;
	}
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new_node;
	return ;
}

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
		perror("minishell: malloc error");
		return (-1);
	}
	else
		*value = NULL;
	return (0);
}

t_env	*ft_init_env_list(char **envp)
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
		if (ft_split_key_value(envp[i], &key, &value))
		{
			//TODO: Clean prior allocation
			return (NULL);
		}
		new_env = ft_env_new(key, value);
		if (new_env == NULL)
		ft_add_env(&env_list, new_env)
		free(key);
		free(value);
		i++;
	}
	return (env_list);
}
