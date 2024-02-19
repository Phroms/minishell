/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrimald <agrimald@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 16:56:15 by agrimald          #+#    #+#             */
/*   Updated: 2023/09/20 21:43:50 by agrimald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	**nodo;
	t_list	*middlemans;

	nodo = lst;
	while (*nodo)
	{
		middlemans = (*lst)->next;
		ft_lstdelone(*lst, del);
		*lst = middlemans;
	}
}
