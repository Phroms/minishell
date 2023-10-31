/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrimald <agrimald@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 16:28:24 by agrimald          #+#    #+#             */
/*   Updated: 2023/09/18 20:18:13 by agrimald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*pointer;
	size_t			i;

	pointer = (unsigned char *)s;
	i = 0;
	while (i < n)
	{
		if (pointer[i] == (unsigned char)c)
			return (&pointer[i]);
		i++;
	}
	return (NULL);
}
/*int main()
{
	char p[50] = "hola como estas";
	int h = 'c';
	printf("%s\n", ft_memchr(p, h, 15));
	char j[50] = "hola como estas";
	int o = 'c';
	printf("%s\n", memchr(j, o, 15));
}*/
