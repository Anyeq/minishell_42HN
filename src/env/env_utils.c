/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asando <asando@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/15 11:32:23 by asando            #+#    #+#             */
/*   Updated: 2026/03/21 20:52:16 by asando           ###   ########.fr       */
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
	else
		(*node)->value = NULL;
	return (0);
}

t_env	*ft_env_new(const char *key, const char *value)
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
	node->next = NULL;
	return (node);
}

void	ft_add_env(t_env **env, t_env *new_node)
{
	t_env	*tmp;

	tmp = *env;
	if (env == NULL)
		return ;
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

void	ft_clean_struct_env(t_env *env_list, char **key, char **value)
{
	t_env	*tmp;
	t_env	*to_delete;

	tmp = env_list;
	to_delete = tmp;
	while (tmp)
	{
		tmp = tmp->next;
		free(to_delete->key);
		free(to_delete->value);
		free(to_delete);
		to_delete = tmp;
	}
	free(*key);
	free(*value);
	return ;
}
