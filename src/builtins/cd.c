/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eynaksho <eynaksho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/04 17:07:57 by eynaksho          #+#    #+#             */
/*   Updated: 2026/03/22 15:25:19 by asando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

static void	set_env_value(t_shell *shell, char *key, char *value)
{
	t_env	*env;

	env = shell->env;
	while (env)
	{
		if (ft_strncmp(env->key, key, ft_strlen(key) + 1) == 0)
		{
			free(env->value);
			env->value = ft_strdup(value);
			return ;
		}
		env = env->next;
	}
	ft_add_env(&shell->env, ft_env_new(key, value));
}

static void	update_pwd(t_shell *shell, char *oldpwd)
{
	char	*cwd;

	set_env_value(shell, "OLDPWD", oldpwd);
	cwd = getcwd(NULL, 0);
	set_env_value(shell, "PWD", cwd);
	free(cwd);
}

static int	go_home(t_shell *shell, char *oldpwd)
{
	char	*home;

	home = get_env_value(shell->env, "HOME");
	if (!home)
	{
		ft_putendl_fd("minishell: cd: HOME not set", 2);
		return (1);
	}
	if (chdir(home) < 0)
	{
		ft_putstr_fd("minishell: cd: ", 2);
		perror(home);
		return (1);
	}
	update_pwd(shell, oldpwd);
	return (0);
}

int	builtin_cd(t_cmd *cmd, t_shell *shell)
{
	char	*path;
	char	*oldpwd;

	oldpwd = getcwd(NULL, 0);
	if (!cmd->args[1])
	{
		go_home(shell, oldpwd);
		free(oldpwd);
		return (0);
	}
	path = cmd->args[1];
	if (chdir(path) < 0)
	{
		ft_putstr_fd("minishell: cd: ", 2);
		perror(path);
		free(oldpwd);
		return (1);
	}
	update_pwd(shell, oldpwd);
	free(oldpwd);
	return (0);
}
