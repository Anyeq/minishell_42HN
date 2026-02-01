/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asando <asando@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 20:02:27 by asando            #+#    #+#             */
/*   Updated: 2026/01/31 20:41:21 by asando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

# include "libft.h"
# include "lexer.h"
# include <stdlib.h>
# include <stdio.h>

typedef struct s_redir
{
	t_token_type	type;
	char			*filename;
	struct s_redir	*next_redir;
}	t_redir;

typedef struct s_cmd
{
	char			**args;
	t_redir			*redirs;
	struct s_cmd	*next_cmd;

}	t_cmd;

//Structure Modification --> parse_free_function.c
t_cmd	*ft_new_cmd(void);
t_redir	*ft_new_redir(t_token_type type, char *filename);
int		ft_add_arg(t_cmd *cmd, char *value);
int		ft_add_redir(t_cmd *cmd, t_token_type type, char *filename);
void	ft_add_cmd(t_cmd **pipeline, t_cmd *new_cmd);

//Data free allocation function --> parse_cmd.c
void	ft_free_args(char **args);
void	ft_free_redirs(t_redir **redirs);
void	ft_free_cmd(t_cmd *cmd);
void	ft_free_pipeline(t_cmd **cmd);

//Parse loop
t_cmd	*parse_loop(t_token *tokens);

#endif
