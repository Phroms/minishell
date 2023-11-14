/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_manager.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrimald <agrimald@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 21:43:15 by agrimald          #+#    #+#             */
/*   Updated: 2023/11/14 16:37:43 by agrimald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/*#include <string.h>
#include <stdlib.h>
#include <stdio.h>*/

/*typedef struct s_env
{
	char	*env_cpy;
}t_env;

typedef struct s_word
{
	char	*word;
	size_t	len;
	int		type;
}t_word;

typedef struct s_tokens
{
	t_word	*words;
	size_t	size;
	t_env	**env;
}t_tokens;

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*chr_dst;
	unsigned char	*chr_src;

	chr_dst = (unsigned char *)dst;
	chr_src = (unsigned char *)src;
	i = 0;
	while (i < n)
	{
		if (chr_dst == NULL && chr_src == NULL)
			return (chr_src);
		chr_dst[i] = chr_src[i];
		i++;
	}
	return (chr_dst);
}

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*ptrdst;
	unsigned char	*ptrsrc;

	ptrdst = (unsigned char *)dst;
	ptrsrc = (unsigned char *)src;
	if (dst == NULL && src == NULL)
		return (0);
	if (dst > src)
	{
		while (len > 0)
		{
			ptrdst[len - 1] = ptrsrc[len - 1];
			len--;
		}
	}
	else
		ft_memcpy(ptrdst, ptrsrc, len);
	return (ptrdst);
}*/

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
	new_word->word = ft_calloc(len + 1,  sizeof(char));
	if (!new_word->word)
		return (0);
	new_word->len = len;
	new_word->type = type;
	new_word->word[len] = '\0';
	ft_memcpy(new_word->word, str, len);
	//ft_memmove(new_word->word, new_word->word + 1, len);
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
			free(tokens->words[i].word);
			i++;
		}
		free(tokens->words);
		free(tokens);
	}
}

/*int main()
{
	t_tokens *tokens = init_token(NULL);

	add_words(tokens, "Hello World", 10000, 0);
	add_words(tokens, "World Hello", 10000, 1);

	size_t i = 0;
	while (i < tokens->size)
	{
		printf("%s\n", tokens->words[i].word);
		i++;
	}
	free_tokens(tokens);
	return (0);
}*/
