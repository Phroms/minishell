/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrimald <agrimald@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 18:47:07 by agrimald          #+#    #+#             */
/*   Updated: 2023/11/14 17:36:12 by agrimald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

/*void	ft_bzero(void	*s, size_t n)
{
	unsigned char	*j;
	size_t			i;

	j = (unsigned char *)s;
	i = 0;
	while (i < n)
	{
		j[i] = 0;
		i++;
	}
}*/

void	ft_bzero(void *s, size_t n)
{
	ft_memset(s, 0, n);
}
/*
int main()
{
	char str[] = "66626956952262";
	char str2[] = "11516666665";
	
	ft_bzero(str, 7);
	printf("Cadena 1 despues de bzero: %s\n", &str[7]);
	
	bzero(str2, 7);
	printf("Cadena 2 despues de bzero: %s\n", &str2[7]);
	
	return 0;
} */
