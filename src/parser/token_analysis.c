/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_analysis.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrimald <agrimald@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 19:16:10 by agrimald          #+#    #+#             */
/*   Updated: 2023/11/18 16:13:11 by agrimald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	special_char(char c)
{
	if (c == '$' || c == '<' || c == '>' || c == '|')
		return (1);
	return (0);
}

int	dst_dots(char *str, char dot)
{
	int	i;

	i = 1;
	if (str[1] == dot)
		return (-2);
	while (str[i] && str[i] != dot)
		i++;
	if (str[i] != '\0')
	{
		printf("error not closing marks\n");
		return (-1);
	}
	return (i - 1);
}

/*size_t	get_char_special(char *token, char next_special_char)
{
	size_t	size;

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
}*/

/*char	get_next_char(char *token)
{
	while (*token)
	{
		if (*token == '|' || *token == '>' || *token == '<')
			return (*token);
		token++;
	}
	return ('\0');
}*/

int	is_marks(t_tokens *tokens, char *str)
{
	int	len;

	len = dst_dots(str, str[0]);
	if (len == -1 || len == -2)
	{
		tokens->error = 1;
		return (1);
	}
	if (len == 0)
		return (len);
	if (str[0] == '"')
		add_words(tokens, str + 1, len, 2);
	if (str[0] == '\'')
		add_words(tokens, str + 1, len, 1);
	return (len + 2);
}

/*bool	search_char(char *token)
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
}*/

int	is_space(t_tokens *tokens, char *str)
{
	int	i;

	i = 0;
	while (str[i] == ' ')
		i++;
	add_words(tokens, " ", 1, 4);
	return (i);
}
