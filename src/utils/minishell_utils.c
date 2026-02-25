/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asando <asando@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 08:22:59 by asando            #+#    #+#             */
/*   Updated: 2026/02/25 08:52:31 by asando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_copy_envp(char **envp)
{
	char	**result;
	int		n_envp;
	int		i;

	n_envp = 0;
	i = 0;
	while (envp[n_envp])
		n_envp++;
	result = malloc(sizeof(char *) * (n_envp + 1));
	if (result == NULL)
	{
		perror("malloc error");
		return (result);
	}
	while (i < n_envp)
	{
		result[i] = ft_strdup(envp[i]);
		if (result[i] == NULL)
		{
			while (i-- > -1)
				free(result[i]);
			free(result);
			return (NULL);
		}
		i++;
	}
	result[n_envp] = NULL;
	return (result);
}
