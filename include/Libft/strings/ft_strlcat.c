/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrimald <agrimald@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 16:49:42 by agrimald          #+#    #+#             */
/*   Updated: 2023/09/18 21:33:56 by agrimald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	len_dst;
	size_t	len_src;
	size_t	i;

	if (!dst || !src)
		return (0);
	if (dstsize == 0)
		return (ft_strlen(src));
	len_dst = ft_strlen(dst);
	len_src = ft_strlen(src);
	if (dstsize <= len_dst)
		return (len_src + dstsize);
	i = 0;
	while (src[i] && len_dst + i < dstsize - 1)
	{
		dst[len_dst + i] = src[i];
		i++;
	}
	dst[len_dst + i] = '\0';
	return (len_dst + len_src);
}

/*int main(void)
{	
    char dest[20] = "ABCDEFGHIJK";
    char src[6] = "12345";

    printf("%zu\n", ft_strlcat(dest, src, 14));
    printf(".%s.\n\n", dest);

    printf("%zu\n", strlcat(dest, src, 14));
    printf(".%s.\n\n", dest);

    return 0;
}*/
