/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_manager.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrimald <agrimald@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 21:43:15 by agrimald          #+#    #+#             */
/*   Updated: 2023/12/05 18:13:09 by agrimald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_tokens	*init_token(t_env **env)
{
	t_tokens *tokens;

	tokens = ft_calloc(1, sizeof(t_tokens));
	if (!tokens)
		return (NULL);
	tokens->words = NULL;
	tokens->size = 0;
	tokens->env = env;
	return (tokens);
}

int my_add_word(t_tokens *tokens, char *str, size_t len, int type)
{
	t_word *new_word = my_new_word(str, len, type);
    if (!new_word) {
        return 0;
    }

    tokens->size += 1;
    t_word *new_array = realloc(tokens->words, tokens->size * sizeof(t_word));
    if (!new_array) {
        free(new_word->word);
        free(new_word);
        return 0;
    }

    tokens->words = new_array;
    tokens->words[tokens->size - 1] = *new_word;

    free(new_word->word);
    free(new_word);
    return 1;
}

t_word *my_new_word(char *str, size_t len, int type)
{
    t_word *word = malloc(sizeof(t_word));
	size_t i;

	i = 0;
    if (!word)
        return NULL;

    word->word = calloc(len + 1, sizeof(char));
    if (!word->word)
    {
        free(word);
        return NULL;
    }

    word->len = len;
    word->type = type;
    //word->next = NULL;
    word->word[len] = '\0';

    while (len-- > 0)
	{
        word->word[len] = str[len];
		i++;
	}
    return word;
}

void	free_tokens(t_tokens *tokens)
{
	size_t	i;

	i = 0;
	if (tokens)
	{
		while (i < tokens->size)
		{
			if (tokens->words[i].word)
				free(tokens->words[i].word);
			i++;
		}
		free(tokens->words);
		free(tokens->str);
		free(tokens);
	}
}

int matrixify(t_tokens *tokens) 
{
    t_word *word;
    size_t i;

    word = tokens->words;
    if (!word)
        return 0;

    tokens->env = (t_env **)ft_calloc(tokens->size + 1, sizeof(t_env *));
    if (!tokens->env)
        return 0;

    i = 0;
    while (i < tokens->size) 
	{
        tokens->env[i] = (t_env *)ft_calloc(1, sizeof(t_env));
        if (!tokens->env[i])
            return 0;

        tokens->env[i]->env_cpy = (char *)ft_calloc(word[i].len + 1, sizeof(char));
        if (!tokens->env[i]->env_cpy)
            return 0;
        // Usar memcpy para copiar la palabra desde la estructura t_word
        memcpy(tokens->env[i]->env_cpy, word[i].word, word[i].len);
        // Agregar manualmente el carácter nulo al final de la palabra
        tokens->env[i]->env_cpy[word[i].len] = '\0';
        // Avanzar a la siguiente palabra
        i++;
    }

    return 1;
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
