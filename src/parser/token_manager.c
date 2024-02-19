/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_manager.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrimald <agrimald@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 21:43:15 by agrimald          #+#    #+#             */
/*   Updated: 2024/02/09 21:21:34 by agrimald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_tokens	*init_token(char **env)
{
	t_tokens	*tokens;

	tokens = malloc(sizeof(t_tokens));
	if (!tokens)
		return (NULL);
	tokens->words = NULL;
	tokens->size = 0;
	tokens->env = env;
	return (tokens);
}

t_word	*create_word(char *str, size_t len, int type)
{
	t_word	*word;

	word = malloc(sizeof(t_word));
	if (!word)
		return (NULL);
	word->word = ft_calloc(len + 1, sizeof(char));
	if (!word->word)
	{
		free(word);
		return (NULL);
	}
	word->len = len;
	word->type = type;
	while (len-- > 0)
		word->word[len] = str[len];
	return (word);
}

int	add_words(t_tokens *tokens, char *str, size_t len, int type)
{
	t_word	*new_word;
	t_word	*new_array;

	new_word = create_word(str, len, type);
	if (!new_word)
		return (0);
	tokens->size += 1;
	new_array = ft_calloc(tokens->size, sizeof(t_word));
	if (!new_array)
	{
		free(new_word->word);
		free(new_word);
		return (0);
	}
	if (tokens->size > 1)
	{
		ft_memcpy(new_array, tokens->words, \
				(tokens->size - 1) * sizeof(t_word));
		free(tokens->words);
	}
	new_array[tokens->size - 1] = *new_word;
	tokens->words = new_array;
	free(new_word);
	return (1);
}

int	matrixify(t_tokens *tokens)
{
	t_word	*word;
	size_t	i;

	word = tokens->words;
	if (!word)
		return (0);
	tokens->env = (char **)ft_calloc(tokens->size + 1, sizeof(char *));
	if (!tokens->env)
		return (0);
	i = 0;
	while (i < tokens->size)
	{
		tokens->env[i] = ft_strdup(word[i].word);
		if (!tokens->env[i])
			return (0);
		i++;
	}
	return (1);
}

void	free_tokens(t_tokens *tokens)
{
	if (tokens)
	{
		free(tokens->words);
		free(tokens);
	}
}

/*int main()
{
	t_tokens *tokens = init_token(NULL);

	add_words(tokens, "Hello World", 5, 0);
	add_words(tokens, "World Hello", 5, 1);

	size_t i = 0;
	while (i < tokens->size)
	{
		printf("%s\n", tokens->words[i].word);
		i++;
	}
	free_tokens(tokens);
	return (0);
}*/
