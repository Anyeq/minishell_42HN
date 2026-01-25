/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asando <asando@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 20:02:27 by asando            #+#    #+#             */
/*   Updated: 2026/01/25 13:16:08 by asando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

#include "libft.h"
#include "lexer.h"

typedef struct	s_redir
{
	t_token_type	type;
	char			*filename;
	struct s_redir	*next_redir;
}	t_redir;

typedef struct	s_cmd
{
	char			**argv;
	t_redir			*redirs;
	struct s_cmd	*next_cmd;

}	t_cmd;

#endif
