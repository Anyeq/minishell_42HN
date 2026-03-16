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

//TODO: change add_env_node with a new one
//TODO: restructuring the function
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
	add_env_node(&shell->env, create_env_node(ft_strdup(key), value));
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
		value = ft_strdup(eq + 1);
		if (!is_valid_identifier(key))
		{
			free(key);
			free(value);
			return (1);
		}
		set_env_var(shell, key, value);
		free(key);
	}
	return (0);
}

int	builtin_export(t_cmd *cmd, t_shell *shell)
{
	int	i;
	int	ret;

	if (!cmd->args[1])
		return (builtin_env(shell));
	ret = 0;
	i = 1;
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
