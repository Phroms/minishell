/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrimald <agrimald@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 16:00:27 by agrimald          #+#    #+#             */
/*   Updated: 2023/09/18 21:36:11 by agrimald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	len;
	size_t	i;
	char	*ptrsrc;
	char	*ptrdest;

	ptrsrc = (char *)src;
	ptrdest = (char *)dst;
	len = ft_strlen(ptrsrc);
	if (dstsize < 1)
		return (len);
	i = 0;
	while (ptrsrc[i] && i < dstsize -1)
	{
		ptrdest[i] = ptrsrc[i];
		i++;
	}
	ptrdest[i] = '\0';
	return (len);
}
/*int main (void)
{
	char dest[50];
	char *src;
	int size;

	src = "Hola wenasSSIWOSka885 como estas";
	size = 50;

	printf("%zu\n", ft_strlcpy(dest, src, size));
	printf(".%s.\n\n", dest);
	printf("%lu\n", strlcpy(dest, src, size));
	printf(".%s.\n\n", dest);
}*/
