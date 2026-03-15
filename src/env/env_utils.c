/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asando <asando@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/15 11:32:23 by asando            #+#    #+#             */
/*   Updated: 2026/03/15 11:41:32 by asando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	else
		node->value = NULL;
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

	tmp = env_list;
	while (tmp)
	{
		tmp = tmp->next;
		free(env_list->key);
		free((env_list->value);
		free((env_list);
	}
	free(*key);
	free(*value);
	return ;
}
