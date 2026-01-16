/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asando <asando@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 13:53:38 by asando            #+#    #+#             */
/*   Updated: 2026/01/16 20:42:59 by asando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

typedef enum	e_token_type
{
	TOKEN_WORD,
	TOKEN_PIPE,
	TOKEN_REDIR_IN,
	TOKEN_REDIR_OUT,
	TOKEN_APPEND,
	TOKEN_HEREDOC,
	TOKEN_EOF
} t_token_type;

typedef enum	e_flag_quote
{
	Q_NONE,
	Q_SINGLE,
	Q_DOUBLE
} t_flag_quote;

typedef struct	s_token
{
	t_token_type	type;
	char			*value;
	t_flag_quote	flag_quote;
	struct s_token	*next_token;
} t_token;

#endif
