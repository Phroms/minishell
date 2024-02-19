/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_errors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrimald <agrimald@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 20:14:52 by agrimald          #+#    #+#             */
/*   Updated: 2024/02/09 16:43:58 by agrimald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_rd(int c)
{
	if (c == '<' || c == '>')
		return (1);
	return (0);
}

int	is_redirection(char *str, int i)
{
	if (i < 2)
		return (0);
	if (!str[i + 1])
		return (1);
	if (str[i] == '>' && str[i + 1] == '>' && str[i + 2] == '>')
		return (1);
	if (i >= 2 && is_rd(str[i - 1]) && is_rd(str[i - 2]) && is_rd(str[i]))
		return (1);
	if (str[i] == '<' && str[i - 1] == '>')
		return (1);
	return (0);
}

int	check_rd(char *str, int i)
{
	if (i <= 0)
		return (1);
	if (!str[i + 1])
		return (1);
	if (str[i - 1] == '<' || str[i - 1] == '>')
		return (1);
	return (0);
}

void	check_redirection_errors(char *str, int i, int *error)
{
	if (str[i] == '>')
	{
		if (is_redirection(str, i))
			*error = printf("syntax error near unexpected token `>'\n");
		else if (str[i + 1] == '>' && str[i + 2] == '>')
			*error = printf("syntax error near unexpected token '>>'\n");
	}
	else if (str[i] == '|')
	{
		if (check_rd(str, i))
			*error = printf("syntax error near unexpected token `|'\n");
	}
	else if (str[i] == '<')
	{
		if (is_redirection(str, i))
			*error = printf("syntax error near unexpected token `<'\n");
		else if (str[i + 1] == '<' && str[i + 2] == '<')
			*error = printf("syntax error near unexpected token '<<'\n");
	}
}

int	check_input(char *str)
{
	int	i;
	int	error;

	i = 0;
	error = 0;
	while (str[i])
	{
		check_redirection_errors(str, i, &error);
		if (error != 0)
			return (1);
		i++;
	}
	return (0);
}
/*int	check_input(char *str)
{
	int	i;
	int	error;

	i = 0;
	error = 0;
	while (str[i])
	{
		if (str[i] == '>')
		{
			if (is_redirection(str, i))
				error = printf("syntax error near unexpected token `>'\n");
			else if (str[i + 1] == '>' && str[i + 2] == '>')
				error = printf("syntax error near unexpected token '>>'\n");
		}
		else if (str[i] == '|')
		{
			if (check_rd(str, i))
				error = printf("syntax error near unexpected token `|'\n");
		}
		else if (str[i] == '<')
		{
			if (is_redirection(str, i))
				error = printf("syntax error near unexpected token `<'\n");
			else if (str[i + 1] == '<' && str[i + 2] == '<')
				error = printf("syntax error near unexpected token '<<'\n");
		}
		if (error != 0)
			return (1);
		i++;
	}
	return (0);
}*/

/*int main() 
{
    char str[] = "ls >output.txt|grep pattern";
    int result = check_input(str);

    if (result == 0) 
	{
        printf("No hay errores de sintaxis en la cadena.\n");
    }
   	else
   	{
        printf("Se encontraron errores de sintaxis en la cadena.\n");
    }
    return 0;
}*/
