/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrimald <agrimald@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 18:27:05 by agrimald          #+#    #+#             */
/*   Updated: 2023/09/18 21:01:51 by agrimald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*ptrs;
	size_t			i;

	ptrs = (unsigned char *)b;
	i = 0;
	while (i < len)
	{
		ptrs[i++] = (unsigned char)c;
	}
	return (ptrs);
}
/*int main()
{
	char p[50] = "hola como estas";
	printf("antes de memset: %s\n", p);
	ft_memset(p, 'p', 5);
	printf("despues: %s\n", p);
	return (0);
}*/
