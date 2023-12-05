/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrimald <agrimald@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 17:25:59 by agrimald          #+#    #+#             */
/*   Updated: 2023/12/05 18:13:52 by agrimald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	break_token(t_tokens *tokens, char *str)
{
	my_add_word(tokens, str, 1, 3);
	return (1);
}

int	is_normal_ch(char ch)
{
	if (special_char(ch) || ch == '#' || ch == '"' \
			|| ch == ' ' || ch == '\'')
		return (1);
	return (0);
}

int	string_tokens(t_tokens *tokens, char *str)
{
	int	i;

	i = 0;
	while (str[i] && !is_normal_ch(str[i]))
		i++;
	my_add_word(tokens, str, i, 0);
	return (i);
}

int	parse_string(t_tokens *tokens, char *str)
{
	int i = 0;
    while (str[i] && str[i] != '#') {
        if (special_char(str[i])) {
            i += break_token(tokens, str + i);
        } else if (str[i] == '"' || str[i] == '\'') {
            i += is_marks(tokens, str + i);
        } else if (str[i] == ' ') {
            i += is_space(tokens, str + i);
        } else {
            i += string_tokens(tokens, str + i);
        }

        if (tokens->error == 1) {
            return 1;
        }
        i++;
    }
    return 0;
}

int	parser(t_tokens *tokens, char *input)
{
	if (!tokens)
    {
        printf("Error: tokens es NULL.\n");
        return 42;
    }

    // Asegurarse de que input no sea NULL
    if (!input)
    {
        printf("Error: input es NULL.\n");
        return 42;
    }

    // Otras operaciones del parser según sea necesario
    tokens->error = 0;
    add_history(input);

    if (check_input(input))
    {
        // Manejar error en check_input
        printf("Error en check_input: algo salió mal.\n");
        return 42;
    }

    parse_string(tokens, input);
    matrixify(tokens);

    return tokens->error;
}
