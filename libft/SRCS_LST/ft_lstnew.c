/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsprigga <bsprigga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/01 16:02:24 by bsprigga          #+#    #+#             */
/*   Updated: 2018/12/06 11:32:31 by bsprigga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

t_list	*ft_lstnew(void const *content, size_t content_size)
{
	t_list *tmp;

	tmp = (t_list *)malloc(sizeof(t_list));
	if (!tmp)
		return (NULL);
	if (!content)
	{
		(*tmp).content = NULL;
		tmp->content_size = 0;
	}
	else
	{
		(*tmp).content = (void *)malloc(content_size);
		if (!(*tmp).content)
		{
			free(tmp);
			return (NULL);
		}
		ft_memcpy((*tmp).content, (void *)content, content_size);
		tmp->content_size = content_size;
	}
	tmp->next = NULL;
	return (tmp);
}
