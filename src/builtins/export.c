/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asando <asando@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/16 18:50:20 by asando            #+#    #+#             */
/*   Updated: 2026/03/22 14:46:55 by asando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

static int	is_valid_identifier(char *str)
{
	int	i;

	if (!str || !str[0])
		return (0);
	if (!ft_isalpha(str[0]) && str[0] != '_')
		return (0);
	i = 1;
	while (str[i] && str[i] != '=')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

static void	set_env_var(t_shell *shell, char *key, char *value)
{
	t_env	*env;

	env = shell->env;
	while (env)
	{
		if (ft_strncmp(env->key, key, ft_strlen(key) + 1) == 0)
		{
			free(env->value);
			env->value = value;
			return ;
		}
		env = env->next;
	}
	ft_add_env(&shell->env, ft_env_new(key, value));
}

static int	export_var(t_shell *shell, char *arg)
{
	char	*eq;
	char	*key;
	char	*value;

	eq = ft_strchr(arg, '=');
	if (eq)
	{
		key = ft_substr(arg, 0, eq - arg);
		value = eq + 1;
		if (!is_valid_identifier(key))
		{
			free(key);
			return (1);
		}
		set_env_var(shell, key, value);
		free(key);
	}
	else
	{
		if (!is_valid_identifier(arg))
			return (1);
		set_env_var(shell, arg, NULL);
	}
	return (0);
}

int	builtin_export(t_cmd *cmd, t_shell *shell)
{
	int		i;
	int		ret;

	ret = 0;
	i = 1;
	if (!cmd->args[1])
		return (builtin_env(shell));
	while (cmd->args[i])
	{
		if (!is_valid_identifier(cmd->args[i]))
		{
			ft_putstr_fd("minishell: export: `", 2);
			ft_putstr_fd(cmd->args[i], 2);
			ft_putendl_fd("': not a valid identifier", 2);
			ret = 1;
		}
		else
			ret = export_var(shell, cmd->args[i]);
		i++;
	}
	return (ret);
}
