/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrimald <agrimald@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 17:24:19 by agrimald          #+#    #+#             */
/*   Updated: 2023/09/20 21:44:43 by agrimald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t		i;
	size_t		j;
	char		*haystack;
	char		*needle;

	i = 0;
	haystack = (char *)big;
	needle = (char *)little;
	if (!*needle)
		return (haystack);
	while (haystack[i] && i < len)
	{
		if (haystack[i] == needle[0])
		{
			j = 1;
			while (needle[j] && i + j < len && haystack[i + j] == needle[j])
				j++;
			if (!(needle[j]))
				return (&haystack[i]);
		}
		i++;
	}
	return (NULL);
}
/*
int main()
{
	char s1[] = "hola buenas como estas, soy manolo";
	char s2[] = "n";
	printf("%s\n", ft_strnstr(s1, s2, 66));
	printf("%ld\n", ft_strnstr(s1, s2, 66) - s1);
	printf("%s\n", strnstr(s1, s2, 66));
	printf("%ld\n", strnstr(s1, s2, 66) - s1);
}*/
