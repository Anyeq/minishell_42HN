/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asando <asando@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/16 18:49:35 by asando            #+#    #+#             */
/*   Updated: 2026/03/22 14:50:08 by asando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

char	*get_env_value(t_env *env, char *key)
{
	int	len;

	if (key == NULL)
		return (NULL);
	len = ft_strlen(key);
	while (env)
	{
		if (ft_strncmp(env->key, key, len + 1) == 0)
			return (env->value);
		env = env->next;
	}
	return (NULL);
}
