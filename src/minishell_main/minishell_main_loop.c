/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_main_loop.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asando <asando@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 11:39:22 by asando            #+#    #+#             */
/*   Updated: 2026/03/13 12:50:20 by asando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	minishell_loop(t_helper *helper)
{
	char	*line;
	t_token	*tokens;
	t_cmd	*pipeline;
	int		expand_status;

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
		line = NULL;
		expand_status = ft_expand_tokens(tokens, helper->envp);
		if (expand_status == -1)
		{
			ft_free_token_list(&tokens);
			continue ;
		}
		pipeline = ft_parse(tokens);
		if (pipeline == NULL)
		{
			ft_free_token_list(&tokens);
			continue ;
		}
		ft_free_token_list(&tokens);
		if (ft_prepare_heredoc(pipeline) == -1)
		{
			ft_free_pipeline(&pipeline);
			continue ;
		}
		ft_executor(&pipeline, helper);
		ft_free_pipeline(&pipeline);
	}
	return ;
}
