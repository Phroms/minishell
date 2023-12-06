/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_to_expand.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojimenez <ojimenez@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 14:04:43 by ojimenez          #+#    #+#             */
/*   Updated: 2023/12/01 11:43:08 by ojimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//nos dice cuantas palabras van a ir en cada matriz
int	len_to_expand(t_tokens *tokens, int *i)
{
	char	*s;
	int		cont;

	cont = 0;
	s = tokens->words[*i].word;
	while (s[0] && s[0] != '<' && s[0] != '>'
		&& s[0] != '|' && *i < (int)tokens->size)
	{
		(*i)++;
		if (tokens->words[*i].word[0] == ' ')
			(*i)++;
		s = tokens->words[*i].word;
		cont++;
	}
	return (cont);
}

//Rellena la matriz con las palabras que tocan y el operador.
//Los espacios no se ponen
void	fill_matrix_to_spand(t_tokens *t, t_expander **exp, int len)
{
	int	i;
	int	j;

	i = 0;
	while (i < len)
	{
		j = -1;
		if (t->words[i].word[0] == ' ')
			i++;
		(*exp)->exp_matr[i] = ft_calloc((size_t)t->words[i].len + 1,
				sizeof(char));
		while (++j < (int)t->words[i].len)
			(*exp)->exp_matr[i][j] = t->words[i].word[j];
		(*exp)->exp_matr[i][j] = '\0';
		i++;
	}
	(*exp)->exp_matr[i][0] = t->words[i].word[0];
	if (t->words[i].word[1] == '<' || t->words[i].word[1] == '>')
	{
		(*exp)->exp_matr[i][1] = t->words[i].word[1];
		(*exp)->exp_matr[i][2] = '\0';
	}
	else
		(*exp)->exp_matr[i][1] = '\0';
}

int	more_types(t_expander **exp, int len)
{
	int	len_prev;
	int	type;

	len_prev = (*exp)->prev->len;
	if ((*exp)->exp_matr[len][0] == '|'
			&& (*exp)->prev->exp_matr[len_prev][0] == '<')
		type = INPIPE;
	if ((*exp)->exp_matr[len][0] == '|'
			&& (*exp)->prev->exp_matr[len_prev][0] == '>')
		type = OUTPIPE;
	if ((*exp)->exp_matr[len][0] == '|'
			&& (*exp)->prev->exp_matr[len_prev][0] == '<'
			&& (*exp)->prev->exp_matr[len_prev][1] == '<')
		type = HEREDOC_PIPE;
	if ((*exp)->exp_matr[len][0] == '|'
			&& (*exp)->prev->exp_matr[len_prev][0] == '>'
			&& (*exp)->prev->exp_matr[len_prev][1] == '>')
		type = APPEND_PIPE;
	return (type);
}

//Escogemos el tipo de expansor de nuestra matriz
int	exp_type_to_expand(t_expander **exp)
{
	int	type;
	int	len;

	type = NONE;
	len = (*exp)->len;
	if ((*exp)->exp_matr[len][0] == '<' && (*exp)->exp_matr[len][1] == '\0')
		type = INP;
	if ((*exp)->exp_matr[len][0] == '>' && (*exp)->exp_matr[len][1] == '\0')
		type = OUTP;
	if ((*exp)->exp_matr[len][0] == '|')
		type = PIPE;
	if ((*exp)->exp_matr[len][0] == '<' && (*exp)->exp_matr[len][1] == '<')
		type = HEREDOC;
	if ((*exp)->exp_matr[len][0] == '>' && (*exp)->exp_matr[len][1] == '>')
		type = APPEND;
	if ((*exp)->prev)
		type = more_types(exp, len);
	return (type);
}


//Hem de separar per <, >, | i despres dir el tipus que toca de cada cosa. 
//Ho fem amb unamatriu que contindra les paraules de cada costat
//la len de cada exp no cuenta el separador
void	exp_split_to_expand(t_tokens *tokens, t_expander **exp)
{
	int			i;
	t_expander	*nodo;

	i = 0;
	nodo = *exp;
	while (i < (int)tokens->size)
	{
		nodo->len = len_to_expand(tokens, &i);
		nodo->exp_matr = ft_calloc((size_t)nodo->len + 1, sizeof(char *));
		fill_matrix_to_spand(tokens, &nodo, i);
		(*exp)->exp_type = exp_type_to_expand(&nodo);
		if (!nodo->next)
		{
			nodo->next = malloc(sizeof(t_expander));
			if (!nodo->next)
			{
				perror("Error al asignar memoria para un nodo");
				exit(EXIT_FAILURE);
			}
			nodo->next->next = NULL;
			nodo->next->prev = nodo;
			nodo = nodo->next;
		}
		i++;
	}
}
