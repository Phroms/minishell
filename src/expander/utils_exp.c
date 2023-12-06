/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_exp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojimenez <ojimenez@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 16:15:24 by ojimenez          #+#    #+#             */
/*   Updated: 2023/11/27 18:00:28 by agrimald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
//si no va hacer con strncmp
int	count_pipes(t_tokens *tokens)
{
	int		count;
	size_t	i;

	count = 0;
	i = 0;
	while (i < tokens->size)
	{
		if (tokens->words[i].word && tokens->words[i].word[0] == '|')
			count++;
		i++;
	}
	return (count);
}
