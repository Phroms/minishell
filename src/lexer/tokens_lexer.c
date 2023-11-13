/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_lexer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrimald <agrimald@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 19:53:53 by agrimald          #+#    #+#             */
/*   Updated: 2023/11/13 17:19:58 by agrimald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "../../include/minishell.h"
#include "minishell.h"


bool	special_char(char corr)
{
	if (corr == '|')
		return (true);
	if (corr == '>')
		return (true);
	if (corr == '<')
		return (true);
	if (corr == ';')
		return (true);
	//if (corr == '&' && next && next == '&') bonuss;
	return (false);
}

size_t	get_char_special(char *token, char next_special_char)
{
	size_t size;

	size = 0;
	while (*token)
	{
		if (*token == next_special_char)
		{
			token++;
			size++;
		}
		else if (*token && *token != next_special_char)
		{
			size++;
			token++;
		}
	}
	return (size);
}

char	get_next_char(char *token)
{
	while (*token)
	{
		if (*token == '|' || *token == '>' || *token == '<' || *token == ';')
			return (*token);
		token++;
	}
	return ('\0');
}

bool	search_char(char *token)
{
	while (*token)
	{
		if (ft_strchr(token, '\'') || ft_strchr(token, '\"'))
				return (false);
		if (ft_strchr(token, '|') || ft_strchr(token, '>') \
				|| ft_strchr(token, '<') || ft_strchr(token, ';'))
		{
			if (ft_strlen(token) != 1)
				return (true);
			return (false);
		}
		token++;
	}
	return (false);
}
