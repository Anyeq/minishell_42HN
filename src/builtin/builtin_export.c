/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asando <asando@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/08 13:32:02 by asando            #+#    #+#             */
/*   Updated: 2026/03/08 13:37:17 by asando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin"

int	builtin_export(char **args, char ***envp)
{
	int	i;

	i = 0;
	if (args[1] == NULL)
	{
		while ((*envp)[i])
		{
			printf("%s\n", (*envp)[i]);
			i++;
		}
		return (0);
	}
	while (args[i])
}

