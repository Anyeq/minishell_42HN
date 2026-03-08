#include "../include/minishell.h"

static int	get_key_len(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	return (i);
}

t_env	*init_env(char **envp)
{
	t_env	*env_list;
	t_env	*node;
	char	*key;
	char	*value;
	int		i;

	env_list = NULL;
	i = 0;
	while (envp[i])
	{
		key = ft_substr(envp[i], 0, get_key_len(envp[i]));
		value = ft_strdup(envp[i] + get_key_len(envp[i]) + 1);
		node = create_env_node(key, value);
		if (node)
			add_env_node(&env_list, node);
		i++;
	}
	return (env_list);
}
