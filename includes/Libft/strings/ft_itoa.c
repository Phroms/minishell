/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrimald <agrimald@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 20:16:35 by agrimald          #+#    #+#             */
/*   Updated: 2023/09/18 21:17:17 by agrimald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static size_t	ft_numero(int n)
{
	size_t	number;

	number = 0;
	if (n == 0)
		number = 1;
	while (n != 0)
	{
		n = n / 10;
		number++;
	}
	return (number);
}

static void	ft_noname(char *str, long int nb, size_t len)
{
	while (len != 0)
	{
		str[len - 1] = nb % 10 + '0';
		nb = nb / 10;
		len--;
	}
}

char	*ft_itoa(int n)
{
	char		*newstr;
	size_t		len;
	long int	nb;
	int			is_negative;

	nb = n;
	is_negative = 0;
	if (nb < 0)
	{
		is_negative = 1;
		nb *= (-1);
	}
	len = ft_numero(n) + is_negative;
	newstr = (char *)ft_calloc(len + 1, sizeof(char));
	if (!newstr)
		return (NULL);
	ft_noname(newstr, nb, len);
	if (is_negative == 1)
		newstr[0] = '-';
	return (newstr);
}
