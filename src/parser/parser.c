/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrimald <agrimald@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 17:25:59 by agrimald          #+#    #+#             */
/*   Updated: 2023/11/16 21:43:25 by agrimald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	break_token(t_tokens *tokens, char *str)
{
	add_words(tokens, str, 1, 3);
	return (1);
}

int	is_normal_ch(char ch)
{
	if (special_char(ch) || ch == '#' || ch == '"' \
			|| ch == ' ' || ch == ''\'')
		return (1);
	return (0);
}

int	string_tokens(t_tokens *tokens, char *str)
{
	int	i;

	i = 0;
	while (str[i] && !is_normal_char(str[i]))
		i++;
	add_words(tokens, str, i, 0);
	return (i);
}

int	parse_string(t_tokens *tokens, char *str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i] && str[i] != '#')
	{
		if (special_char(str[i]))
			i += break_token(tokens, str + i);
		else if (str[i] == '"' || str[i] == '\'')
			i += is_marks(tokens, str + i);
		else if (str[i] == ' ')
			i += is_space(tokens, str + i);
		else
			i += string_tokens(tokens, str + i);
		if (tokens->error == 1)
			return (1);
		j++;
	}
	return (0);
}

int	parser(t_tokens *tokens)
{
	tokens->error = 0;
	add_history(tokens->str);
	if (check_input(tokens->str))
		return (42);
	parse_string(tokens, tokens, str);
	matrixify(tokens);
	return (tokens->error);
}
