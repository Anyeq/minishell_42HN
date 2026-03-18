/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asando <asando@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/22 11:05:01 by asando            #+#    #+#             */
/*   Updated: 2026/03/18 19:03:08 by asando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion.h"

char	*ft_join_and_free(char *str1, char *str2)
{
	char	*res;

	res = ft_strjoin(str1, str2);
	if (res == NULL)
	{
		perror("minishell: malloc error");
		free(str1);
		free(str2);
		return (NULL);
	}
	free(str1);
	free(str2);
	return (res);
}
