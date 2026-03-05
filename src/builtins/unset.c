/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eynaksho <eynaksho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/05 21:41:18 by eynaksho          #+#    #+#             */
/*   Updated: 2026/03/05 21:41:19 by eynaksho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	remove_env_var(t_shell *shell, char *key)
{
	t_env	*env;
	t_env	*prev;

	env = shell->env;
	prev = NULL;
	while (env)
	{
		if (ft_strncmp(env->key, key, ft_strlen(key) + 1) == 0)
		{
			if (prev)
				prev->next = env->next;
			else
				shell->env = env->next;
			free(env->key);
			free(env->value);
			free(env);
			return ;
		}
		prev = env;
		env = env->next;
	}
}

int	builtin_unset(t_cmd *cmd, t_shell *shell)
{
	int	i;

	i = 1;
	while (cmd->args[i])
	{
		remove_env_var(shell, cmd->args[i]);
		i++;
	}
	return (0);
}
