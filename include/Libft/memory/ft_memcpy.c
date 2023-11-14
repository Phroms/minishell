/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrimald <agrimald@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 20:55:17 by agrimald          #+#    #+#             */
/*   Updated: 2023/11/14 16:42:01 by agrimald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

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
		if (dst == NULL && src == NULL)
			return (dst);
		chr_dst[i] = chr_src[i];
		i++;
	}
	return (dst);
}
