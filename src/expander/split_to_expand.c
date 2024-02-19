/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_to_expand.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojimenez <ojimenez@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 14:04:43 by ojimenez          #+#    #+#             */
/*   Updated: 2024/02/06 12:33:53 by ojimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//Miramos que no haya << o >> ya que tenemos que ponerlo, sino solo el '\0'
void	fill_token(t_tokens *t, t_expander **exp, int k, int flag)
{
	if (flag)
	{
		(*exp)->token = malloc(((int)t->words[k].len + 1) * sizeof(char));
		if (!(*exp)->token)
		{
			perror("Error al asignar memoria en un malloc");
			exit(EXIT_FAILURE);
		}
		(*exp)->token[0] = t->words[k].word[0];
		if ((int)t->words[k].len == 2 && (t->words[k].word[1] == '<'
				|| t->words[k].word[1] == '>'))
		{
			(*exp)->token[1] = t->words[k].word[1];
			(*exp)->token[2] = '\0';
		}
		else
			(*exp)->token[1] = '\0';
	}
	else
	{
		(*exp)->token = malloc(1 * sizeof(char));
		(*exp)->token[0] = '\0';
	}
}

//Rellena la matriz con las palabras que tocan y el operador.
//Los espacios no se ponen
void	fill_matrix_to_spand(t_tokens *t, t_expander **exp, int len, int flag)
{
	int	cont;
	int	i;
	int	j;

	i = 0;
	cont = -1;
	while (++cont < len)
	{
		j = -1;
		if (t->words[t->i_exp].word[0] == ' ')
			t->i_exp++;
		(*exp)->exp_matr[i] = malloc((t->words[t->i_exp].len + 1)
				* sizeof(char));
		if (!(*exp)->exp_matr[i])
			malloc_error();
		while (++j < (int)t->words[t->i_exp].len)
			(*exp)->exp_matr[i][j] = t->words[t->i_exp].word[j];
		(*exp)->exp_matr[i][j] = '\0';
		i++;
		t->i_exp++;
	}
	if (flag == 1 && t->words[t->i_exp].word[0] == ' ')
		t->i_exp++;
	(*exp)->exp_matr[i] = NULL;
	fill_token(t, exp, t->i_exp, flag);
}

int	more_types(t_expander **exp)
{
	int	type;

	type = NONE;
	if ((*exp)->prev->token[0] == '<' || (*exp)->prev->token[0] == '>')
		type = FD;
	if (((*exp)->prev->token[0] == '>' || (*exp)->prev->token[0] == '<')
		&& (*exp)->token[0] == '>')
		type = OUTP_FD;
	if (((*exp)->prev->token[0] == '>' || (*exp)->prev->token[0] == '<')
		&& (*exp)->token[0] == '>' && (*exp)->token[1] == '>')
		type = APPEND_FD;
	if (((*exp)->prev->token[0] == '<' || (*exp)->prev->token[0])
		&& (*exp)->token[0] == '<')
		type = INP_FD;
	if ((*exp)->token[0] == '<' && (*exp)->prev->token[0] == '|')
		type = INP;
	if ((*exp)->token[0] == '>' && (*exp)->prev->token[0] == '|')
		type = OUTP;
	if ((*exp)->prev->token[0] == '|' && (*exp)->token[0] == '<'
		&& ft_strlen((*exp)->token) == 2)
		type = HEREDOC_PIPE;
	if ((*exp)->prev->token[0] == '|' && (*exp)->token[0] == '>'
		&& ft_strlen((*exp)->token) == 2)
		type = APPEND_PIPE;
	return (type);
}

//Escogemos el tipo de expansor de nuestra matriz
int	exp_type_to_expand(t_expander **exp)
{
	int	type;

	type = NONE;
	if ((*exp)->token[0] == '<' && ft_strlen((*exp)->token) == 1)
		type = INP;
	if ((*exp)->token[0] == '>' && ft_strlen((*exp)->token) == 1)
		type = OUTP;
	if ((*exp)->token[0] == '|')
		type = PIPE;
	if ((*exp)->token[0] == '<' && ft_strlen((*exp)->token) == 2)
		type = HEREDOC;
	if ((*exp)->token[0] == '>' && ft_strlen((*exp)->token) == 2)
		type = APPEND;
	if ((*exp)->prev)
		type = more_types(exp);
	return (type);
}

//Hem de separar per <, >, | i despres dir el tipus que toca de cada cosa. 
//Ho fem amb una matriu que contindra les paraules de cada costat
//la len de cada exp no cuenta el separador
//La flag es per mirar si hi ha un \0 a la pos 0
void	exp_split_to_expand(t_tokens *tokens, t_expander **exp)
{
	int			flag;
	t_expander	*nodo;

	tokens->i_exp = 0;
	nodo = *exp;
	while (tokens->i_exp < (int)tokens->size)
	{
		flag = 0;
		nodo->len = len_to_expand(tokens, &flag);
		nodo->exp_matr = ft_calloc((size_t)(nodo->len + 1), sizeof(char *));
		fill_matrix_to_spand(tokens, &nodo, nodo->len, flag);
		(nodo)->exp_type = exp_type_to_expand(&nodo);
		if (tokens->i_exp < (int)tokens->size && !nodo->next)
		{
			create_node(&nodo);
			nodo = nodo->next;
			nodo->exp_type = 0;
		}
		tokens->i_exp++;
	}
}
