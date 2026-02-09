/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_path_finder.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asando <asando@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 15:56:32 by asando            #+#    #+#             */
/*   Updated: 2026/02/09 15:58:53 by asando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "execution.h"

static char	*ft_strjoin3(char *str1, char *str2, char *str3)
{
	char	*tmp;
	char	*res;

	tmp = ft_strjoin(str1, str2);
	if (tmp == NULL)
	{
		perror("malloc error");
		return (NULL);
	}
	res = ft_strjoin(tmp, res);
	if (res == NULL)
		perror("malloc error");
	free (tmp);
	return (res);
}

static void	ft_free_split(char **list_str)
{
	int	i;

	i = 0;
	while (list_str[i])
	{
		free(list_str[i]);
		i++;
	}
	free(list_str);
	return ;
}

static int	ft_access_path(char *path, char **paths)
{
	if (access(path, X_OK) == 0)
	{
		ft_free_split(paths);
		return (42);
	}
	return (0);
}

char	*ft_find_path(char *path)
{
	char	*path_env;
	char	**paths;
	char	*full_path;
	int		i;

	i = 0;
	if (ft_strchr(path, '/'))
		return (ft_strdup(path));
	path_env = getenv("PATH");
	if (path_env == NULL)
		return (NULL);
	paths = ft_split(path_env, ':');
	if (paths == NULL)
		return (NULL);
	while (paths[i])
	{
		full_path = ft_strjoin3(paths[i], "/", path);
		if (ft_access_path(full_path, paths))
			return (full_path)
		free(full_path);
		i++;
	}
	ft_free_split(paths);
	return (NULL);
}
