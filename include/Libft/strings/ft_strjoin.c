/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrimald <agrimald@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 13:08:48 by agrimald          #+#    #+#             */
/*   Updated: 2023/09/18 21:31:03 by agrimald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	len_s1;
	size_t	len_s2;
	char	*res;
	char	*ptrs1;

	if (!(ft_strlen(s1)) && !(ft_strlen(s2)))
		return (ft_strdup(""));
	ptrs1 = (char *)s1;
	len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
	res = (char *) malloc(sizeof(char) * ((len_s1 + len_s2) + 1));
	if (res == NULL)
		return (NULL);
	ft_memmove(res, ptrs1, len_s1 + 1);
	ft_strlcat(res, s2, (len_s1 + len_s2) + 1);
	return (res);
}
/*int main()
{
	const char *g = "Hola";
    const char *h = "mundo";
    char *resultado = ft_strjoin(g, h);
   	printf("Resultado: %s\n", resultado);
}*/
