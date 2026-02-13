/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_main_loop.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asando <asando@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 11:39:22 by asando            #+#    #+#             */
/*   Updated: 2026/02/13 12:10:07 by asando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	minishell_loop(t_helper *helper)
{
	char	*line;
	t_token	*tokens;
	t_cmd	*pipeline;

	while (1)
	{
		line = readline("minishell$ ");
		if (line == NULL)
		{
			printf("exit\n");
			break ;
		}
		if (*line == '\0')
		{
			free(line);
			continue ;
		}
		add_history(line);
		tokens = ft_lexer_loop(line);
		if (tokens == NULL)
		{
			free(line);
			continue ;
		}
		free(line);
		// TODO: Expansion here
		pipeline = ft_parse(tokens);
		if (pipeline == NULL)
		{
			//TODO: clean tokens properly
			continue ;
		}
		//TODO: clean tokens properly
		ft_executor(&pipeline, helper);
		//TODO: clean pipeline properly
	}
	return ;
}
