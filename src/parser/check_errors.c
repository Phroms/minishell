/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_errors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrimald <agrimald@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 20:14:52 by agrimald          #+#    #+#             */
/*   Updated: 2023/11/06 22:01:54 by agrimald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	is_rd(int c)
{
	if (c == '<' || c == '>')
		return (1);
	return (0);
}

int is_redirection(char *str, int i)
{
	if (str[i + 1] == '\0')
		return (1);
	if (i < 2)
		return (0);
	if (is_rd(str[i - 1]) && is_rd(str[i - 2]) && is_rd(str[i]))
		return (1);
	if (str[i] == '<' && str[i - 1] == '>')
		return (1);
	return (0);
}

int	check_rd(char *str, int i)
{
	if (str[i] == '<' || str[i] == '>')
		return (1);
	if (str[i + 1] == '\0')
		return (1);
	if (str[i - 1] == '<' || str[i - 1] == '>')
		return (1);
	return (0);
}

int	check_input(char *str)
{
	int i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '>' || str[i] == '<' || str[i] == '|')
		{
			if (str[i + 1] == '>' || str[i + 1] == '<')
				ft_printf("syntax error near unexpected token '%c'\n", str[i]);
			if (str[i + 1] == '|')
				ft_printf("syntax error near unexpected token '|'\n");
			return (1);
		}
		i++;
	}
	return (0);
}

/*int main() {
    char str[] = "ls >output.txt|grep pattern";
    int result = check_input(str);

    if (result == 0) {
        printf("No hay errores de sintaxis en la cadena.\n");
    } else {
        printf("Se encontraron errores de sintaxis en la cadena.\n");
    }

    return 0;
}*/
