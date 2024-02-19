/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrimald <agrimald@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 21:01:11 by agrimald          #+#    #+#             */
/*   Updated: 2023/09/18 21:38:22 by agrimald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	size_t			slen;
	char			*ptrs;
	unsigned int	i;

	if (!s)
		return (NULL);
	slen = ft_strlen(s);
	ptrs = malloc(slen + 1 * sizeof(char));
	if (!ptrs)
		return (NULL);
	i = 0;
	while (s[i] > 0)
	{
		ptrs[i] = f(i, s[i]);
		i++;
	}
	ptrs[i] = '\0';
	return (ptrs);
}
