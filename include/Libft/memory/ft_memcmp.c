/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrimald <agrimald@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 18:16:06 by agrimald          #+#    #+#             */
/*   Updated: 2023/09/18 20:31:18 by agrimald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*ptrs1;
	unsigned char	*ptrs2;
	size_t			i;

	ptrs1 = (unsigned char *)s1;
	ptrs2 = (unsigned char *)s2;
	i = 0;
	while (i < n)
	{
		if (*ptrs1 != *ptrs2)
			return (*ptrs1 - *ptrs2);
		ptrs1++;
		ptrs2++;
		i++;
	}
	return (0);
}
/*int main()
{
	char s1[] = "a ya no se que p\200oner lol";
	char s2[] = "ola ya no se que poner lal";
	printf("%d\n", ft_memcmp(s1, s2, 50));
	printf("%d\n", memcmp(s1, s2, 50));
}*/
