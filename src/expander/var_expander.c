/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_expander.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojimenez <ojimenez@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 12:08:31 by ojimenez          #+#    #+#             */
/*   Updated: 2023/12/06 11:50:41 by ojimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//En str guardamos la variable a expandir reserbandole memoria.
//Le quitamos las " " y el &
char	*allocate_str_expanded(t_tokens *tokens, int i, int flag)
{
	int	j;
	int		k;
	char	*str;

	j = 0;
	k = 0;
	str = malloc((tokens->words[i].len - flag) * sizeof(char));
	if (!str)
	{
		perror("Error al asignar memoria en un malloc");
		exit(EXIT_FAILURE);
	}
	while (j < (int)tokens->words[i].len)
	{
		if (tokens->words[i].word[j] != '"' && tokens->words[i].word[j] != '&')
		{
			str[k] = tokens->words[i].word[j];
			k++;
		}
		j++;
	}
	str[k] = '\0';
	return (str);
}

//Ponemos en tokens->words la nueva palabra reemplazandola a la anterior
void	replace_str_expanded(t_tokens *tokens, char *s_changed, int pos)
{
	int	len;
	int	i;

	len = ft_strlen(s_changed);
	i = 0;
	free(tokens->words[pos].word);
	tokens->words[pos].word = malloc((len + 1) * sizeof(char));
	while (i < len)
	{
		tokens->words[pos].word[i] = s_changed[i];
		i++;
	}
	tokens->words[pos].word[i] = '\0';
	tokens->words[pos].len = len;
}

//Miramos las variables que tenemos que expandir
void	exp_expand_var(t_tokens *tokens)
{
	int		i;
	char	*str;
	char	*s_changed;

	i = 0;
	while (i < (int)tokens->size)
	{
		if (tokens->words[i].word[0] == '&' || (tokens->words[i].word[1] == '&'
				&& tokens->words[i].word[0] == '"'))
		{
			if (tokens->words[i].word[0] == '"')
				str = allocate_str_expanded(tokens, i, 2);
			else
				str = allocate_str_expanded(tokens, i, 0);
			s_changed = getenv(str);
			if (s_changed != NULL)
				replace_str_expanded(tokens, s_changed, i);
			free (str);
		}
		i++;
	}
}
