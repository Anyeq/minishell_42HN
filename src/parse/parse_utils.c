/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asando <asando@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/01 19:28:12 by asando            #+#    #+#             */
/*   Updated: 2026/02/01 19:31:03 by asando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

void	ft_parse_error(t_cmd **pipeline)
{
	perror("minishell: failed malloc");
	ft_free_pipeline(pipeline);
	return ;
}
