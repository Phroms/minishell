/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_manager.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrimald <agrimald@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 21:43:15 by agrimald          #+#    #+#             */
/*   Updated: 2023/11/13 22:14:21 by agrimald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_tokens	*init_token(t_env **env)
{
	t_tokens *tokens;

	tokens = malloc(sizeof(t_tokens));
	if (!tokens)
		return (NULL);
	tokens->words = NULL;
	tokens->size = 0;
	tokens->env = env;
	return (tokens);
}

int	add_words(t_tokens *tokens, char *str, size_t len, int type)
{
	t_word	*new_word;

	if (!str)
		return (0);
	tokens->words = realloc(tokens->words, (tokens->size + 1) * sizeof(t_word));
	if (!tokens->words)
		return (0);
	new_word = &tokens->words[tokens->size];
	new_word->word = malloc((len + 1) * sizeof(char *));
	if (!new_word->word)
		return (0);
	new_word->len = len;
	new_word->type = type;
	new_word->word[len] = '\0';
	ft_memcpy(new_word->word, str, len);
	ft_memmove(new_word->word, new_word->word + 1, len);
	tokens->size += 1;
	return (1);
}

void	free_tokens(t_tokens *tokens)
{
	size_t	i;

	i = 0;
	if (tokens)
	{
		while (i < tokens->size)
		{
			free(tokens->word[i].word);
			i++;
		}
		free(tokens->word);
		free(tokens);
	}
}

int main()
{
	t_tokens *tokens = init_token(NULL);

	add_word = (tokens, "Hello", 5, 0);
	add_word = (tokens, "World", 5, 1);

	size_t i = 0;
	while (i < tokens->size)
	{
		printf("%s\n", tokens->words[i].word);
		i++;
	}
	free_tokens(tokens);
	return (0);
}
