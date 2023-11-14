/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrimald <agrimald@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 18:33:35 by agrimald          #+#    #+#             */
/*   Updated: 2023/11/14 17:36:23 by agrimald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	*ft_calloc(size_t number, size_t size)
{
	void	*ptr;

	ptr = malloc(number * size);
	if (!ptr)
	{
		errno = ENOMEM;
		return (NULL);
	}
	ft_memset(ptr, 0, number * size);
	return (ptr);
}
