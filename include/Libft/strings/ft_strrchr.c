/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrimald <agrimald@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 14:14:42 by agrimald          #+#    #+#             */
/*   Updated: 2023/09/20 21:45:09 by agrimald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strrchr(const char *s, int c)
{
	unsigned int	i;
	char			*ptrs;

	ptrs = NULL;
	i = 0;
	while (s[i])
	{
		if (s[i] == (char)c)
			ptrs = (char *)&s[i];
		i++;
	}
	if ((char)c == s[i])
		return ((char *)&s[i]);
	return (ptrs);
}
/*int main()
{
	char s[] = "hola woenass";
	int c = 'o';
	printf("%s", ft_strrchr(s, c));
}*/
